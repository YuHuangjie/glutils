#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <vector>

#include "gl.h"

int CompileShader(const char *vertex_code, const char *frag_code, std::string &error)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Create shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile Vertex Shader
    glShaderSource(VertexShaderID, 1, &vertex_code, NULL);
    glCompileShader(VertexShaderID);
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (!Result) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        error = std::string("VERTEX ERROR: ") + std::string(VertexShaderErrorMessage.data());
        return 0;
    }

    // Compile Fragment Shader
    glShaderSource(FragmentShaderID, 1, &frag_code, NULL);
    glCompileShader(FragmentShaderID);
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (!Result) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        error = std::string("FRAGMENT ERROR: ") + std::string(FragmentShaderErrorMessage.data());
        return 0;
    }

    // Link the program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (!Result) {
            std::vector<char> ProgramErrorMessage(InfoLogLength);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            error = std::string("LINK ERROR: ") + std::string(ProgramErrorMessage.data());
            return 0;
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

#endif
