/*#pragma once

#include <vector>
#include "Program.hpp"
#include "FilePath.hpp"

struct cursorCubeProgram{
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;
    GLint uCubeColor;

    CubeProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "../../../../shaders/3D.vs.glsl", applicationPath.dirPath() + "../../../../shaders/normals.fs.glsl")){
        //texture
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uCubeColor = glGetUniformLocation(m_Program.getGLId(), "uCubeColor");
    }
};*/