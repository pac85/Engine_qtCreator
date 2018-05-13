#ifndef RENDERSYS_H
#define RENDERSYS_H

#include "../vk/vkMain.h"

class RenderSYS
{
public:
    RenderSYS(string appname, GLFWwindow* window, Settings settings);

    vkMain * vk_main;
};

#endif // RENDERSYS_H
