// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Windowing/NovelRTWindowingService.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.h"
#include <list>

std::list<std::shared_ptr<NovelRT::Windowing::WindowingService>> _windowCollection;
std::list<std::shared_ptr<NovelRT::Input::InteractionService>> _interactionServiceCollection;
std::list<std::unique_ptr<NovelRT::Input::BasicInteractionRect>> _rectCollection;

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif


NovelRTInteractionService NovelRT_InteractionService_create(const NovelRTWindowingService windowingService) {
  _windowCollection.push_back(std::shared_ptr<Windowing::WindowingService>(reinterpret_cast<Windowing::WindowingService*>(windowingService)));
  _interactionServiceCollection.push_back(std::make_shared<Input::InteractionService>(Input::InteractionService(_windowCollection.back())));
  return reinterpret_cast<NovelRTInteractionService>(_interactionServiceCollection.back().get());
}

int32_t NovelRT_InteractionService_consumePlayerInput(NovelRTInteractionService service) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);
  if (servicePtr == nullptr) {
        return NOVELRT_FAILURE;
    }
  servicePtr->consumePlayerInput();  
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_InteractionService_executeClickedInteractable(const NovelRTInteractionService service) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);
  if (servicePtr == nullptr) {

        return NOVELRT_FAILURE;
  }
  servicePtr->executeClickedInteractable();
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_InteractionService_setScreenSize(const NovelRTInteractionService service, NovelRTGeoVector2F value) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);
  if (servicePtr == nullptr) {

        return NOVELRT_FAILURE;
  }
  auto vector = reinterpret_cast<Maths::GeoVector2F&>(value);
  servicePtr->setScreenSize(vector);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_InteractionService_getKeyState(const NovelRTInteractionService service, NovelRTKeyCode value, NovelRTKeyStateFrameChangeLog* output) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);
  if (servicePtr == nullptr || output == nullptr) {

        return NOVELRT_FAILURE;
  }
  auto changelog = servicePtr->getKeyState(reinterpret_cast<Input::KeyCode&>(value));
  *output = reinterpret_cast<NovelRTKeyStateFrameChangeLog&>(changelog);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_InteractionService_createBasicInteractionRect(const NovelRTInteractionService service, const NovelRTTransform transform, int layer, NovelRTBasicInteractionRect* outputRect) {
  auto servicePtr = reinterpret_cast<Input::InteractionService*>(service);
  if (servicePtr == nullptr) {

        return NOVELRT_FAILURE;
  }

  _rectCollection.push_back(std::unique_ptr<Input::BasicInteractionRect>(servicePtr->createBasicInteractionRect(*reinterpret_cast<const Transform*>(&transform), layer)));
  *outputRect = reinterpret_cast<NovelRTBasicInteractionRect>(_rectCollection.back().get());
  return NOVELRT_SUCCESS;
}

#ifdef __cplusplus
}
#endif