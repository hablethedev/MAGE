cmake_minimum_required(VERSION 3.28)
project(Mage)

set(SOURCES
    src/main.cpp
)

set(IMGUI_SOURCES
    lib/cmake-imgui/imgui/imgui.cpp
    lib/cmake-imgui/imgui/imgui_demo.cpp
    lib/cmake-imgui/imgui/imgui_draw.cpp
    lib/cmake-imgui/imgui/imgui_widgets.cpp
    src/glad.c
)

find_package(glfw3 3.3 REQUIRED)
include_directories(src/lib/)
add_executable(mage src/main.cpp src/glad.c)
target_link_libraries(mage glfw)
add_executable(MyIMGUIApp ${SOURCES} ${IMGUI_SOURCES})
target_include_directories(MyIMGUIApp PRIVATE imgui)
