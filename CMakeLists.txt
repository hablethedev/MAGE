cmake_minimum_required(VERSION 3.28)
project(Mage)

set(SOURCES
    src/main.cpp
)

set(IMGUI_SOURCES
    src/lib/cmake-imgui/imgui/imgui.cpp
    src/lib/cmake-imgui/imgui/imgui_draw.cpp
    src/lib/cmake-imgui/imgui/imgui_widgets.cpp
    src/lib/cmake-imgui/imgui/imgui_tables.cpp
    src/lib/cmake-imgui/imgui/backends/imgui_impl_glfw.cpp
    src/lib/cmake-imgui/imgui/backends/imgui_impl_opengl3.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(glfw3 3.3 REQUIRED)
include_directories(src/lib/cmake-imgui/imgui)
include_directories(src/lib/)
add_executable(mage ${SOURCES} src/glad.c ${IMGUI_SOURCES})
target_link_libraries(mage glfw)
target_include_directories(mage PRIVATE imgui)
