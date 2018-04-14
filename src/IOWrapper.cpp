#include "IOWrapper.h"

IOWrapper::IOWrapper(string appname, Settings settings)
{
    //initializes glfw
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Settings::setting height, width, b_full_screen;
    if(!(  settings.get_setting("height", height)
           && settings.get_setting("width", width)
           && settings.get_setting("full_screen", b_full_screen)))
    {
    }

    //creates the windows
    window = glfwCreateWindow(width.get_val<int>(), height.get_val<int>(), appname.c_str(), b_full_screen.get_val<bool>()? glfwGetPrimaryMonitor() : nullptr, nullptr);
    //if(window == NULL) slog << err("unable to create window");
}
