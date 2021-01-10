cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Pong)

# NOTE: from CppND-Capstone-Snake-Game Repo (still not necessary)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")  

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

# Optional add SDL_image lib:
# TODO: add CMake file see or add to path. 
# see: https://stackoverflow.com/a/44900762
#      https://trenki2.github.io/blog/2017/07/04/using-sdl2-image-with-cmake/
# NOTE: uncomment following lines if  you are using SDL_image library
#find_package(SDL2_image REQUIRED) 
#include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
# NOTE: REMEMBER to add element to target_link_libraries: ${SDL2_IMAGE_LIBRARIES}

add_executable(PongGame src/main.cpp src/ball.cpp src/paddle.cpp)

# NOTE: from CppND-Capstone-Snake-Game Repo (still not necessary)
# add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(PongGame ${SDL2_LIBRARIES}) #NOTE: Use this if no sdl_image is used on code.
target_link_libraries(PongGame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}) # NOTE: use this if you need SDL_Image features; requires install the library on workspace!
# NOTE: to install the SDL_Image library type on linux-terminal: sudo apt-get install libsdl2-image-dev 

# Copy images/ folder and content to build/ folder:
add_custom_command(TARGET PongGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/images/ $<TARGET_FILE_DIR:PongGame>/images/)