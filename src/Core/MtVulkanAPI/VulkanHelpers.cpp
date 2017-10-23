//
// Created by MTesseracT on 21-10-2017.
//

#include "VulkanHelpers.hpp"

vk::Bool32 VulkanHelpers::GetSupportedDepthFormat(vk::PhysicalDevice p_physicalDevice, vk::Format *p_depthFormat)
{
    std::vector<vk::Format> depthFormats = {
            vk::Format::eD32SfloatS8Uint,
            vk::Format::eD32Sfloat,
            vk::Format::eD24UnormS8Uint,
            vk::Format::eD16UnormS8Uint,
            vk::Format::eD16Unorm
    };

    for (auto& format : depthFormats)
    {
        vk::FormatProperties formatProps = p_physicalDevice.getFormatProperties(format);

        if(formatProps.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
        {
            *p_depthFormat = format;
            return static_cast<vk::Bool32>(true);
        }
    }

    return static_cast<vk::Bool32>(false);
}

QueueFamilyIndices VulkanHelpers::FindQueueFamilies(vk::PhysicalDevice p_device, vk::SurfaceKHR p_surface)
{
    QueueFamilyIndices indices;

    std::vector<vk::QueueFamilyProperties> queueFamilies = p_device.getQueueFamilyProperties();

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
        {
            indices.graphicsFamily = i;
        }

        vk::Bool32 presentSupport = p_device.getSurfaceSupportKHR(i, p_surface);

        if (queueFamily.queueCount > 0 && presentSupport)
        {
            indices.presentFamily = i;
        }

        if (indices.IsComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}

SwapChainSupportDetails VulkanHelpers::QuerySwapChainSupport(vk::PhysicalDevice p_device, vk::SurfaceKHR p_surface)
{
    SwapChainSupportDetails details{
            p_device.getSurfaceCapabilitiesKHR(p_surface),
            p_device.getSurfaceFormatsKHR(p_surface),
            p_device.getSurfacePresentModesKHR(p_surface)
    };
    return details;
}

std::string VulkanHelpers::GetDeviceTypeName(vk::PhysicalDeviceType p_type)
{
    switch (p_type)
    {
        case vk::PhysicalDeviceType::eOther:         return "Other";
        case vk::PhysicalDeviceType::eIntegratedGpu: return "Integrated";
        case vk::PhysicalDeviceType::eDiscreteGpu:   return "Discrete";
        case vk::PhysicalDeviceType::eVirtualGpu:    return "Virtual";
        case vk::PhysicalDeviceType::eCpu:           return "CPU";
    }
}

bool VulkanHelpers::CheckDeviceExtensionSupport(vk::PhysicalDevice p_device, std::vector<const char*> p_reqExtensions)
{
    std::vector<vk::ExtensionProperties> availableExtensions = p_device.enumerateDeviceExtensionProperties(nullptr);

    std::set<std::string> requiredExtensions(p_reqExtensions.begin(), p_reqExtensions.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}