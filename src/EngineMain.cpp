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
#include "EngineMain.h"
#include "common.h"

#include <vulkan/vulkan.h>

#include "Ptr.h"
#include "Base.h"
#include "Function.h"
#include "Settings.h"
#include "logger.h"
#include "render/StaticMesh.h"
#include "vk/vkMain.h"
#include "ActorSYS/World.h"
#include "ActorSYS/DummyActor.h"

EngineMain::EngineMain(string appname)
{
    this->appname = appname;
}

EngineMain::~EngineMain()
{
    //dtor
}

void EngineMain::init()
{
    slog << "initializing...";
    Settings base_settings("./cfg/basic_settings.cfg");

    //initializes glfw
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    //reads resolution from config file
    Settings::setting height, width, b_full_screen;
    base_settings.get_setting("height", height);
    base_settings.get_setting("width", width);
    base_settings.get_setting("full_screen", b_full_screen);

    //creates the windows
    window = glfwCreateWindow(width.get_val<int>(), height.get_val<int>(), appname.c_str(), b_full_screen.get_val<bool>()? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if(window == NULL) slog << err("unable to create window");

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appname.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    vector<const char*> device_extensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkSurfaceFormatKHR sf{VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    VkPresentModeKHR pm= VK_PRESENT_MODE_FIFO_KHR;
    VkExtent2D extent = {width.get_val<int>(), height.get_val<int>()};

    vkMain testmain(appInfo, window, device_extensions, sf, pm, extent);
}

void EngineMain::loop()
{
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;
    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        /*test_world.UpdateWorld(deltaTime);
        cout << "\r" << 1.0 / deltaTime << "       ";*/
    }
}
