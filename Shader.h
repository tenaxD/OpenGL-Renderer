#pragma once
#include "glm/glm.hpp"

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void Use();
    void SetMat4(const char* name, glm::mat4 value);
    void SetBool(const char* name, bool value);
private:
    unsigned int vertexShader, fragmentShader;
    unsigned int shaderProgram;
};