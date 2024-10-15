cmake_minimum_required(VERSION 3.27)
project(HeimskrEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(imgui)
find_package(glfw3)
find_package(glad)

add_executable(HeimskrEngine main.cpp)

target_link_libraries(HeimskrEngine
        imgui::imgui
        glfw
        glad::glad)