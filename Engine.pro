TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += `pkg-config --static --libs glfw3` -lvulkan

DISTFILES += \
    src/licenser.sh \
    src/toadd.txt \
    src/ActorSYS/oldWorld/World2.cpp \
    src/ActorSYS/oldWorld/World2.h  \
    src/ActorSYS/oldWorld/World.cpp \
    src/ActorSYS/oldWorld/World.h

HEADERS += \
    include/logger.h \
    include/vkGraphicsQueue.h \
    src/ActorSYS/Actor.h \
    src/ActorSYS/BaseActor.h \
    src/ActorSYS/Component.h \
    src/ActorSYS/DummyActor.h \
    src/ActorSYS/Transform.h \
    src/game/GameMain.h \
    src/InputSYS/engineIn.h \
    src/render/Camera.h \
    src/render/Material.h \
    src/render/ModelComponent.h \
    src/render/PointLightComponent.h \
    src/render/StaticMesh.h \
    src/vk/vkDeleter.hpp \
    src/vk/vkDevice.h \
    src/vk/vkExceptions.h \
    src/vk/vkGraphicsQueue.h \
    src/vk/vkImageView.h \
    src/vk/vkInit.hpp \
    src/vk/vkInstance.h \
    src/vk/vkMain.h \
    src/vk/vkPhysicalDevice.h \
    src/vk/vkPresentQueue.h \
    src/vk/vkQueue.h \
    src/vk/vkQueueFamilies.h \
    src/vk/vkQueues.h \
    src/vk/vkShaderModule.h \
    src/vk/vkShaderStage.h \
    src/vk/vkSurface.h \
    src/vk/vkSurfaceInfo.h \
    src/vk/vkSwapChain.h \
    src/vk/vkTransferQueue.h \
    src/vk/vkUtils.h \
    src/Base.h \
    src/common.h \
    src/EngineMain.h \
    src/logger.h \
    src/Loop.h \
    src/Profiler.h \
    src/Ptr.h \
    src/Singleton.h \
    src/Task.h \
    src/render/Texture.h \
    src/ActorSYS/internal_actors.h \
    src/game/actors.h \
    src/ActorSYS/World.h \
    src/ActorSYS/ActorIndexers.hpp \
    src/ResourceManager/ResourceManager.h \
    src/render/RenderSYS.h \
    src/IOWrapper.h \
    src/Settings.h

SOURCES += \
    src/ActorSYS/Actor.cpp \
    src/ActorSYS/BaseActor.cpp \
    src/ActorSYS/Component.cpp \
    src/ActorSYS/DummyActor.cpp \
    src/ActorSYS/Transform.cpp \
    src/game/GameMain.cpp \
    src/InputSYS/engineIn.cpp \
    src/render/Camera.cpp \
    src/render/Material.cpp \
    src/render/ModelComponent.cpp \
    src/render/PointLightComponent.cpp \
    src/render/StaticMesh.cpp \
    src/vk/vkDevice.cpp \
    src/vk/vkGraphicsQueue.cpp \
    src/vk/vkImageView.cpp \
    src/vk/vkInstance.cpp \
    src/vk/vkMain.cpp \
    src/vk/vkPhysicalDevice.cpp \
    src/vk/vkPresentQueue.cpp \
    src/vk/vkQueue.cpp \
    src/vk/vkQueueFamilies.cpp \
    src/vk/vkQueues.cpp \
    src/vk/vkShaderModule.cpp \
    src/vk/vkShaderStage.cpp \
    src/vk/VkSurface.cpp \
    src/vk/vkSwapChain.cpp \
    src/vk/vkTransferQueue.cpp \
    src/vk/vkUtils.cpp \
    src/Base.cpp \
    src/dummy.cpp \
    src/EngineMain.cpp \
    src/logger.cpp \
    src/Loop.cpp \
    src/main.cpp \
    src/Profiler.cpp \
    src/Ptr.cpp \
    src/common.cpp \
    src/render/Texture.cpp \
    src/ActorSYS/World.cpp \
    src/ResourceManager/ResourceManager.cpp \
    src/render/RenderSYS.cpp \
    src/IOWrapper.cpp \
    src/Settings.cpp
