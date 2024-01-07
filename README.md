# Project Amethyst

Amethyst is a open-source project for making client-side mods for Minecraft Bedrock version `1.20.51.1`. Amethyst provides headers based on the vanilla game, as well as some general purpose APIs for using Minecrafts input system.

# Mod Functions
A mod is able to export functions that will be automatically called by AmethystRuntime.
```cpp
// Called when a mod is loaded by AmethystAPI, used to create hooks
extern "C" __declspec(dllexport) void Initialize();

// Called every 50ms, currently not hooked into a real tick function
extern "C" __declspec(dllexport) void OnTick();

// ClientInstance::onStartJoinGame
extern "C" __declspec(dllexport) void OnStartJoinGame(ClientInstance* clientInstance);

// Hooked ScreenView::setupAndRender for mods to draw UI
extern "C" __declspec(dllexport) void OnRenderUI(ScreenView* screenView, UIRenderContext* ctx);

// Used to destroy hooks for hot-reloading
extern "C" __declspec(dllexport) void Shutdown();
```

# CMakeLists.txt Template
```cmake
cmake_minimum_required(VERSION 3.12)
project(ModName) # Replace with the name of your mod
set(MOD_VERSION "1.0.0") # Replace with the version of your mod

# C++ Build Settings
set(CMAKE_CONFIGURATION_TYPES "RelWithDebInfo" CACHE STRING "Build configurations" FORCE)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo" FORCE)
set(CMAKE_CXX_STANDARD 20)

# Build into %appdata%/Amethyst
set(AmethystFolder "$ENV{appdata}/Amethyst")
set(UWPAmethystFolder "$ENV{LOCALAPPDATA}/Packages/Microsoft.MinecraftUWP_8wekyb3d8bbwe/AC/Amethyst")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${UWPAmethystFolder}/mods/${PROJECT_NAME}@${MOD_VERSION}")

# Include Amethyst
find_library(AMETHYST_API AmethystAPI PATHS "${AmethystFolder}/lib")
include_directories(${AmethystFolder}/include "include/")

# Project Files
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE H_FILES "src/*.h")
add_library(${PROJECT_NAME} SHARED ${CPP_SOURCES} ${H_FILES})

# EnTT Config Options
target_compile_definitions(${PROJECT_NAME} PUBLIC ENTT_PACKED_PAGE=128)

# Pass MOD_VERSION to the source code
target_compile_definitions(${PROJECT_NAME} PRIVATE MOD_VERSION="${MOD_VERSION}")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${AMETHYST_API})
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/fmt.lib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${AmethystFolder}/lib/libMinHook.x64.lib")
```