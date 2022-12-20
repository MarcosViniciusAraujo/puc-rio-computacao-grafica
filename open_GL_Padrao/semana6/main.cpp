#include <GL/gl3.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "buffer.h"
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

static GLuint vao;
static GLuint pid;

static void createScene (void)
{
  float coord[] = {
    -0.5f,-0.5f, 0.0f,
     0.5f,-0.5f, 0.0f,
     0.0f, 0.5f, 0.0f
  };
  float color[] = {
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
  };
  glGenVertexArrays(1,&vao);
  glBindVertexArray(vao);
  GLuint id[2];
  glGenBuffers(2,id);
  glBindBuffer(GL_ARRAY_BUFFER,id[0]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(coord),coord,GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,id[1]);
  glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
  glEnableVertexAttribArray(1);
}

static void buildProgram ()
{
  GLuint vid = CreateShader(GL_VERTEX_SHADER,"vertex.glsl");
  GLuint fid = CreateShader(GL_FRAGMENT_SHADER,"fragment.glsl");
  pid = CreateProgram(vid,fid,0);
}

static void initialize ()
{
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  buildProgram();
  createScene();
}

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
}

static void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize (GLFWwindow* win, int width, int height)
{
  glViewport(0,0,width,height);
}

static void display (GLFWwindow* win)
{
  float ident[16] = {
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f
  };
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(pid);
  GLint loc = glGetUniformLocation(pid,"mvp");
  glUniformMatrix4fv(loc,1,GL_FALSE,ident);

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES,0,3);
}

static void idle (GLFWwindow* win)
{
}

int main ()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);       // required for mac os
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_TRUE);  // option for mac os

  //glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
  
  glfwSetErrorCallback(error);

  GLFWwindow* win = glfwCreateWindow(600,400,"Window title",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  
  glfwMakeContextCurrent(win);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();

  while(!glfwWindowShouldClose(win)) {
    //idle(win);
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
