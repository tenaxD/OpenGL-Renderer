#pragma once
class ShaderSources {
public:
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "uniform bool hasTexture;\n"
    "void main()\n"
    "{\n"
    "   if (hasTexture)\n"
    "       FragColor = texture(texture1, TexCoord);\n"
    "   else\n"
    "       FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";
};