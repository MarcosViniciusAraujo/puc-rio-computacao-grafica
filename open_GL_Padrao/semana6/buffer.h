#ifndef BUFFER_H
#define BUFFER_H

#include <GL/gl.h>

GLuint CreateVAO (void);
void DeleteVAO (GLuint vao);

GLuint CreateBuffer (GLenum target, GLsizeiptr size, const GLvoid* data);
void VertexAttribPointer (GLuint index, GLint size, GLenum type, 
                          GLboolean norm, GLsizei stride, 
                          const GLvoid* offset);
void DeleteBuffer (GLuint id);

#endif

