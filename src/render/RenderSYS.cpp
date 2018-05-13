#include "RenderSYS.h"

RenderSYS::RenderSYS(string appname, GLFWwindow *window, Settings settings)
{
    //reads resolution from config file
    Settings::setting height, width, b_full_screen;
    base_settings.get_setting("height", height);
    base_settings.get_setting("width", width);
    base_settings.get_setting("full_screen", b_full_screen);

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appname.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = appname + " engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    vector<const char*> device_extensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkSurfaceFormatKHR sf{VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    VkPresentModeKHR pm= VK_PRESENT_MODE_FIFO_KHR;
    VkExtent2D extent = {width.get_val<int>(), height.get_val<int>()};

    vk_main = new vkMain(appInfo, window, device_extensions, sf, pm, extent);
}
