cmake_minimum_required(VERSION 3.28)
project(Mage)

set(SOURCES
    src/main.cpp
    src/glad.c
)

set(IMGUI_SOURCES
    src/lib/cmake-imgui/imgui/imgui.cpp
    src/lib/cmake-imgui/imgui/imgui_demo.cpp
    src/lib/cmake-imgui/imgui/imgui_draw.cpp
    src/lib/cmake-imgui/imgui/imgui_widgets.cpp
    src/glad.c
)

find_package(glfw3 3.3 REQUIRED)
include_directories(src/lib/)
add_executable(mage ${SOURCES} ${IMGUI_SOURCES})
target_link_libraries(mage glfw)
target_include_directories(mage PRIVATE imgui)
