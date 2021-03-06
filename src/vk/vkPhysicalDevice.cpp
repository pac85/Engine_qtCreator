/**************************************************************************/
/*
  Copyright (C) 2017 Antonino Maniscalco (alias pac85)

  This file is part of Engine.

  Engine is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Engine is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Engine.  If not, see http://www.gnu.org/licenses/

*/
/**************************************************************************/
#include "vkPhysicalDevice.h"
#include "vkSurfaceInfo.h"

#include "../logger.h"

vkPhysicalDevice::vkPhysicalDevice(vkInstance &instance, vkSurface &surface, vector<const char*> * requiered_device_extensions)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance.instance, &deviceCount, nullptr);

    if(deviceCount == 0)
    {
        slog << err("no device with vulkan support found");
        return;
    }

    device_extensions = *requiered_device_extensions;

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance.instance, &deviceCount, devices.data());

    if(!select_device(devices, physical_device, &queue_families, surface, requiered_device_extensions))
    {
        slog << err("no suitable device found");
        return;
    }

    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physical_device, &deviceProperties);

    slog << msg(string("chosen device:") + deviceProperties.deviceName);
}

vkPhysicalDevice::~vkPhysicalDevice()
{
    //dtor
}

//choses the best device it can find, has to be changed to something
// that lets the user chose the hardware to be used
bool vkPhysicalDevice::select_device
(
    std::vector<VkPhysicalDevice> &devices,
    VkPhysicalDevice &chosen_device,
    vkQueueFamilies * queue_families,
    vkSurface &surface,
    vector<const char*> * device_extensions
)
{
    bool suitable_dev_found = false;
    unsigned int best_score = 0;
    for (const auto& device : devices)
    {
        unsigned int score = 0;
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;

        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){score+= 1000;}

        if(!deviceFeatures.geometryShader){score-= 1000000;}

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        /*checks that all the needed queue families are supported */
        bool graphics_found = false, present_found = false;
        int i = 0;
        for(const auto& queueFamily : queueFamilies)
        {
            if (!graphics_found && queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                graphics_found = true;
                queue_families->graphics.index = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface.surface, &presentSupport);

            if (!present_found && queueFamily.queueCount > 0 && presentSupport)
            {
                present_found = true;
                queue_families->present.index = i;
            }

            queue_families->transfer.index = queue_families->graphics.index;

            if(present_found && graphics_found){break;}//if it finds both there is no point in keeping looking for queue families

            i++;
        }
        if(!(graphics_found && present_found)){continue;}//if it didn't find both cues go to next device

        /*checking for device specific extnsions support*/
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(device_extensions->begin(), device_extensions->end());
        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }

        if(!requiredExtensions.empty()){continue;}

        /*checks that swap chains are supported*/
        bool swapChainAdequate = false;

        vkSurfaceInfo swapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.present_modes.empty();


        if(score >= best_score)
        {
            chosen_device = device;
            suitable_dev_found = true;
            best_score = score;
        }

        if(!swapChainAdequate){continue;}

    }
    return suitable_dev_found;   //if no device is found
}

