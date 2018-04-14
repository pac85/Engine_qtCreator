#ifndef IOWRAPPER_H
#define IOWRAPPER_H

#include "common.h"
#include "Settings.h"

class IOWrapper
{
public:
    IOWrapper(string, Settings);

   GLFWwindow* get_window()
    {
        return window;
    }
private:
    GLFWwindow* window;
};

#endif // IOWRAPPER_H
