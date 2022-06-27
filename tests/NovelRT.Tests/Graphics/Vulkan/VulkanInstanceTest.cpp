// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>
#include <vulkan/vulkan.h>

using namespace NovelRT;

TEST(VulkanInstanceTest, canCreateVulkanInstance)
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Engine_Tests";
    appInfo.pEngineName = "NovelRT";
    appInfo.apiVersion = VK_API_VERSION_1_2;
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkInstance instance = VK_NULL_HANDLE;
    ASSERT_NO_THROW(vkCreateInstance(&createInfo, nullptr, &instance));
    ASSERT_NO_THROW(vkDestroyInstance(instance, nullptr));
}