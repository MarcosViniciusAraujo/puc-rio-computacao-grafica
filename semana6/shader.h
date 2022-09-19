#ifndef SHADER_H
#define SHADER_H

#include <GL/gl.h>

GLuint CreateShader (GLenum shadertype, const char* filename);
GLuint CreateProgram (int sid, ...);

#endif
