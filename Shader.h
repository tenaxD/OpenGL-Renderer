#pragma once

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void Use();
private:
    unsigned int vertexShader, fragmentShader;
    unsigned int shaderProgram;
};