# g++ -o bin/mage src/main.cpp src/glad.c -lglfw -lGL -ldl -Isrc/include/
g++ -o bin/mage src/main.cpp src/glad.c src/imgui/imgui.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_widgets.cpp src/imgui/imgui_tables.cpp src/imgui/imgui_impl_glfw.cpp src/imgui/imgui_impl_opengl3.cpp -I src/include -lglfw -lGL -ldl
