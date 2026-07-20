![3D Renderer](Example.png)
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

# Usage instructions
To import an fbx you have to paste this into the code in Application.cpp like this:
models.push_back(new Model("PathToYourModel"));

The model should be triangulated and if you want your textures they have to be embedded in the .fbx

To create a triangle or a cube you call either of those two methods:
meshes.push_back(Primitives::CreateTriangle());
meshes.push_back(Primitives::CreateCube());

You might want to adjust the position and scale of the meshes/models, to do that just edit this code in Application.h:
std::vector<glm::vec3> meshPositions = {
		glm::vec3(6.0f, 0.0f,  0.0f),
		glm::vec3(8.0f, 0.0f,  0.0f),
		glm::vec3(10.0f, 0.0f,  0.0f)
};
std::vector<glm::vec3> modelPositions = {
	glm::vec3(0.0f, 0.0f,  0.0f),
	glm::vec3(2.0f, 0.0f,  0.0f),
	glm::vec3(4.0f, 0.0f,  0.0f)
};
//Add a new position by adding a comma, then glm::vec3(provide 3 values)
        
std::vector<float> modelScales = {1.0f //to add you need to put a comma after a previous value and add another scale as a float}; //it scales in the same order that you import your models 