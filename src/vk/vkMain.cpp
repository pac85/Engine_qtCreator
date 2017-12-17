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
#include "vkMain.h"
#include "../logger.h"

vkMain::vkMain( VkApplicationInfo app_info,
                GLFWwindow * window,
                vector<const char*> device_extensions,
                VkSurfaceFormatKHR surface_format,
                VkPresentModeKHR present_mode,
                VkExtent2D extent)
{

    const std::vector<const char*> validationLayers = {"VK_LAYER_LUNARG_standard_validation"};

    slog << msg("creating instance");
    instance  = new vkInstance(app_info, true, &validationLayers);

    slog << msg("creating surface");
    surface = new vkSurface(window, *instance);

    slog << msg("creating physical device");
    physical_device = new vkPhysicalDevice(*instance, *surface, &device_extensions);

    slog << msg("creating logical device");
    device = new vkDevice(*instance, *physical_device, &device_extensions);


    slog << msg("creating swapchain");

    vkSwapChainDesiredProperties dprops(surface_format, present_mode, extent);

    vkSurfaceInfo surface_info(physical_device->physical_device, *surface);

    swap_chain = new vkSwapChain(*physical_device, *device, *surface, surface_info, dprops, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
}


vkMain::~vkMain()
{
    delete(swap_chain);
    delete(device);
    delete(physical_device);
    delete(surface);
    delete(instance);
}

void vkMain::recreate_swap_chain(VkSurfaceFormatKHR surface_format, VkPresentModeKHR present_mode, VkExtent2D extent)
{
    //makes shure that we don't destroy anything that is still being used
    get_device().wait_idle();

    delete(swap_chain);

    //recreates the swap chain
    vkSwapChainDesiredProperties dprops(surface_format, present_mode, extent);
    vkSurfaceInfo surface_info(physical_device->physical_device, *surface);
    swap_chain = new vkSwapChain(*physical_device, *device, *surface, surface_info, dprops, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
}

/*
    get_device().wait_idle();

    delete(instance);
    delete(surface);
    delete(physical_device);
    delete(device);
    delete(swap_chain);

    vkMain(app_info, window, device_extensions, surface_format, present_mode, extent);
*/
