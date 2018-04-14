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
#include <vulkan/vulkan.h>

#include "Ptr.h"
#include "Base.h"
#include "Function.h"
#include "Settings.h"
#include "logger.h"
#include "vk/vkInstance.h"
#include "vk/vkSurface.h"
#include "vk/vkPhysicalDevice.h"
#include "vk/vkDevice.h"
#include "vk/vkSwapChain.h"
#include "vk/vkShaderModule.h"
#include "render/StaticMesh.h"
#include "vk/vkMain.h"
#include "ActorSYS/World.h"
#include "ActorSYS/DummyActor.h"
#include "EngineMain.h"

char* work_dir;

class GameProgram
{
    public:
        void run() {
            init();
            mainLoop();
        }

    private:
        void init()
        {

        }

        void mainLoop()
        {

        }
};

void start_game()
{

}

int main(int argc, char *argv[]) {
    //HelloTriangleApplication app;

    work_dir = argv[0];

    /*#ifdef DEBUG
        use_validation_layers = true;
    #else
        use_validation_layers = false;
    #endif // DEBUG*/

    bool game_editor = false;   //if false game mode will be initialized, otherwise editor mode

    for(int i = 1;i<argc;i++)
    {
        string arg(argv[i]);
        if(!arg.compare("-edit"))
        {
            game_editor = true;
        }
    }

    //Init("test");

    EngineMain test("test app");
    test.init();
    test.loop();

    /*world test_world;

    DummyActor* da1;

    for(int i = 0; i < 1000000;i++)
    {
        da1 = new DummyActor;
        test_world.add_actor(da1);
    }

    DummyActor* da2 = new DummyActor;
    test_world.add_actor(da2);

    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;

    test_world.aa_attach(test_world.create_attachment(da1, da2));

    while (!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        test_world.UpdateWorld(deltaTime);
        cout << "\r" << 1.0 / deltaTime << "       ";
    }

    cout << endl;*/

   /*Ptr<Base> test;

    test = "test";


    try {
        start_game();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }*/
    if(!game_editor)
    {
        GameProgram CGame;
    }

    return EXIT_SUCCESS;
}
