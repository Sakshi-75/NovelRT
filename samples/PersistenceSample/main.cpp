
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository
// root for more information.

#include <NovelRT/NovelRT.h>

using namespace NovelRT::Ecs;
using namespace NovelRT::Input;
using namespace NovelRT::PluginManagement;
using namespace NovelRT::Persistence;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    NovelRT::LoggingService logger = NovelRT::LoggingService();
    logger.setLogLevel(NovelRT::LogLevel::Info);

    DefaultPluginSelector selector;
    auto windowingProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>();
    auto inputProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IInputPluginProvider>();
    auto resourceManagementProvider = selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>();

    auto scheduler =
        Configurator()
            .WithDefaultSystemsAndComponents()
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(windowingProvider)
            .WithPluginProvider(inputProvider)
            .WithPluginProvider(resourceManagementProvider)
            .InitialiseAndRegisterComponents();

    std::shared_ptr<NovelRT::Ecs::Graphics::DefaultRenderingSystem> renderingSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Graphics::DefaultRenderingSystem>();

    NovelRT::Threading::FutureResult<NovelRT::Ecs::Graphics::TextureInfo> textureFuture =
        renderingSystem->GetOrLoadTexture("novel-chan");

    renderingSystem->ForceVertexTextureFutureResolution();

    auto transformBuffer = scheduler.GetComponentCache().GetComponentBuffer<TransformComponent>();
    auto entityGraphBuffer = scheduler.GetComponentCache().GetComponentBuffer<EntityGraphComponent>();

    EntityId parentEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    EntityId childOfChildEntity =
        renderingSystem->CreateSpriteEntityOutsideOfSystem(textureFuture.GetBackingConcurrentSharedPtr(), scheduler);

    transformBuffer.PushComponentUpdateInstruction(
        0, childEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    transformBuffer.PushComponentUpdateInstruction(
        0, childOfChildEntity,
        TransformComponent{NovelRT::Maths::GeoVector3F(200, 200, 0), NovelRT::Maths::GeoVector2F::zero(), 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childEntity, EntityGraphComponent{true, parentEntity, 0});
    entityGraphBuffer.PushComponentUpdateInstruction(0, childOfChildEntity, EntityGraphComponent{true, childEntity, 0});

    NovelRT::Timing::Timestamp secondsPassed(0);
    Chapter chapterToLoad;

    scheduler.RegisterSystem(
        [&](auto delta, auto catalogue)
        {
            secondsPassed += delta;

            if (secondsPassed >= NovelRT::Timing::Timestamp::fromSeconds(3))
            {
                secondsPassed = NovelRT::Timing::Timestamp(0);
                chapterToLoad = Chapter::FromEcsInstance(scheduler.GetComponentCache());
                resourceManagementProvider->GetResourceLoader()->SavePackage("MyChapter.chapter", chapterToLoad.ToFileData());
                chapterToLoad.LoadFileData(resourceManagementProvider->GetResourceLoader()->LoadPackage("MyChapter.chapter"));
                //chapterToLoad.ToEcsInstance(scheduler.GetComponentCache()); IF YOU WANT TO SEE THE FILE SIZE GROW FOREVER, UNCOMMENT THIS!
            }
            else
            {
                ComponentView<TransformComponent> transforms = catalogue.template GetComponentView<TransformComponent>();

                for (auto [entity, transform] : transforms)
                {
                    TransformComponent newComponent{};
                    newComponent.rotationInRadians =
                        NovelRT::Maths::Utilities::DegreesToRadians(20 * delta.getSecondsFloat());
                    newComponent.scale = NovelRT::Maths::GeoVector2F::zero();
                    transforms.PushComponentUpdateInstruction(entity, newComponent);
                }
            }
        });

    scheduler.GetComponentCache().PrepAllBuffersForNextFrame(std::vector<EntityId>{});

    NovelRT::Timing::StepTimer timer;

    auto windowPtr = windowingProvider->GetWindowingDevice();
    windowPtr->SetWindowTitle("Persistence Test");

    std::shared_ptr<NovelRT::Ecs::Input::InputSystem> inputSystem =
        scheduler.GetRegisteredIEcsSystemAs<NovelRT::Ecs::Input::InputSystem>();

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    while (!windowPtr->GetShouldClose())
    {
        windowPtr->ProcessAllMessages();
        timer.tick(DummyUpdateStuff);
    }

    return 0;
}
