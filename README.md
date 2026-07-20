# 3D Renderer
A 3D renderer written in C++ using OpenGL, GLFW, GLAD, Assimp and stb_image.

## Features
- FBX/OBJ model importing
- Viewport camera with mouse look
- Texture support for imported models
- Primitive shapes (cube, triangle)

## Controls
- WASD – move
- Q/E – up/down
- Left Shift – sprint
- Mouse – look around
- Escape – exit

### Dependencies (manual setup required)
- GLFW – add to Additional Include Directories and Library Directories
- GLAD – add glad.c to Source Files
- GLM – header only, add to Additional Include Directories
- Assimp – install via vcpkg: `vcpkg install assimp`
- stb_image – included in project

## Building
This project was built with Visual Studio 2022 on Windows.