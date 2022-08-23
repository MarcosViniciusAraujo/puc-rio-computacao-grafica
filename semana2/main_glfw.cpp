/*
  Marcos Vinicius Araujo Almeida - 1910869  
  Felipe Frighetto Gonzalez - 1910438
*/
#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#else
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#endif

#include "arcball.h"
#include "camera.h"
#include "objlight.h"
#include "material.h"
#include "transform.h"
#include "cube.h"
#include "cube_array.h"
#include "sphere.h"
#include "pyramid_array.h"

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.0f, 4.0f};

static Camera* camera;
static Arcball* arcball;
static Light* light;

static Material* red;
static Material* gray;
static Material* blue;
static Material* purple;
static Material* orange;
static Material* green;
static Material* gold;

static Transform* trf;
static Transform* trfCube;
static Transform* trfPosPernaMesa1;
static Transform* trfPosPernaMesa2;
static Transform* trfPosPernaMesa3;
static Transform* trfPosPernaMesa4;
static Transform* trfEsfera;
static Transform* trfCenterCube1;
static Transform* trfCenterCube2;
static Transform* trfCenterCube3;
static Transform* trfPiramide;

static Shape* cube;
static Shape* centerCube1;
static Shape* centerCube2;
static Shape* centerCube3;
static Shape* perna1;
static Shape* perna2;
static Shape* perna3;
static Shape* perna4;
static Sphere* esfera;
static PyramidArray* piramide;

static void initialize (void)
{
  const float pernaMesaX = 0.2f, 
    pernaMesaY = 1.5f, 
    pernaMesaZ = 0.2f;
  
  // set background color: white 
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);
  // enable lighting computation 
  glEnable(GL_LIGHTING);
  // enable normalization of normal vectors 
  glEnable(GL_NORMALIZE);

  camera = new Camera(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  arcball = camera->CreateArcball();
  light = new ObjLight(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  
  //cores
  red = new Material(1.0f,0.0f,0.0f);
  gray = new Material(0.8f,0.8f,0.8f);
  blue = new Material(0.0f, 0.0f, 1.0f);
  purple = new Material(0.5f, 0.1f, 0.7f);
  orange = new Material(0.8f, 0.4f, 0.0f);
  green = new Material(0.0f, 1.0f, 0.0f);
  gold = new Material(0.8f, 0.7f, 0.2f);
  
  //tampão da mesa
  trf = new Transform();
  trf->Scale(3.0f,0.2f,3.0f);
  trf->Translate(0.0f,-1.0f,0.0f);

  //transformação para perna da mesa
  trfPosPernaMesa1 = new Transform();
  trfPosPernaMesa1->Translate(-1.4f, -1.5f, -1.4f);
  trfPosPernaMesa1->Scale(pernaMesaX, pernaMesaY, pernaMesaZ);

  trfPosPernaMesa2 = new Transform();
  trfPosPernaMesa2->Translate(-1.4f, -1.5f, 1.4f);
  trfPosPernaMesa2->Scale(pernaMesaX, pernaMesaY, pernaMesaZ);

  trfPosPernaMesa3 = new Transform();
  trfPosPernaMesa3->Translate(1.4f, -1.5f, -1.4f);
  trfPosPernaMesa3->Scale(pernaMesaX, pernaMesaY, pernaMesaZ);

  trfPosPernaMesa4 = new Transform();
  trfPosPernaMesa4->Translate(1.4f, -1.5f, 1.4f);
  trfPosPernaMesa4->Scale(pernaMesaX, pernaMesaY, pernaMesaZ);

  //transformação do cubo
  trfCube = new Transform();
  trfCube->Scale(0.5f, 0.3, 0.5f);
  trfCube->Translate(-1.0f, 0.0f, -1.0f);
  trfCube->Rotate(30.0f, 0.0f, 1.0f, 0.0f);

  //transformação da esfera
  trfEsfera = new Transform();
  trfEsfera->Scale(0.3f, 0.3f, 0.3f);
  trfEsfera->Translate(3.0f, 1.0f, 0.0f);

  //transformação do cubo central
  trfCenterCube1 = new Transform();
  trfCenterCube1->Scale(0.7f, 0.7f, 0.7f);
  trfCenterCube1->Translate(0.0f, 0.0f, 0.7f);

  //trasformação do cubo acima
  trfCenterCube2 = new Transform();
  trfCenterCube2->Scale(0.3f, 0.5f, 0.3f);
  trfCenterCube2->Translate(0.0f, 1.4f, 1.6f);

  //transformação do cubo de trás muito escondido (🤫)
  trfCenterCube3 = new Transform();
  trfCenterCube3->Scale(0.2f, 0.2f, 0.2f);
  
  //transformação da piramide
  trfPiramide = new Transform();
  trfPiramide->Scale(0.7f, 0.7f, 0.7f);
  trfPiramide->Translate(0.8f, 0.0f, -1.0f);

  //objetos da mesa
  cube = new CubeArray();
  esfera = new Sphere();
  centerCube1 = new CubeArray();
  centerCube2 = new CubeArray();
  centerCube3 = new CubeArray();
  piramide = new PyramidArray();

  //pernas da mesa
  perna1 = new CubeArray();
  perna2 = new CubeArray();
  perna3 = new CubeArray();
  perna4 = new CubeArray();
}

static void error (int code, const char* msg)
{
  printf("GLFW error %d: %s\n", code, msg);
  glfwTerminate();
  exit(0);
}

static void display (GLFWwindow * win)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  camera->Setup();
  light->Setup();
  trf->Load();
  gray->Load();
  cube->Draw();
  trf->Unload();
  red->Load();
  trfCube->Load();
  cube->Draw();
  trfCube->Unload();

  //pernas da mesa
  gray->Load();
  trfPosPernaMesa1->Load();
  perna1->Draw();
  trfPosPernaMesa1->Unload();

  trfPosPernaMesa2->Load();
  perna2->Draw();
  trfPosPernaMesa2->Unload();

  trfPosPernaMesa3->Load();
  perna3->Draw();
  trfPosPernaMesa3->Unload();

  trfPosPernaMesa4->Load();
  perna4->Draw();
  trfPosPernaMesa4->Unload();

  //esfera
  trfEsfera->Load();
  blue->Load();
  esfera->Draw();
  trfEsfera->Unload();

  //cubo central
  trfCenterCube1->Load();
  purple->Load();
  centerCube1->Draw();
  trfCenterCube1->Unload();

  //cubo central acima
  trfCenterCube2->Load();
  orange->Load();
  centerCube2->Draw();
  trfCenterCube2->Unload();

  //cubo escodindo demais
  trfCenterCube3->Load();
  green->Load();
  centerCube3->Draw();
  trfCenterCube3->Unload();

  //piramide
  trfPiramide->Load();
  gold->Load();
  piramide->Draw();
  trfPiramide->Unload();

}

static void resize (GLFWwindow* win, int width, int height)
{
  glViewport(0,0,width,height);
}

static void keyboard(GLFWwindow * window, int key, int scancode, int action, int mods)
{
 if (key == GLFW_KEY_Q && action == GLFW_PRESS)
  glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursorpos (GLFWwindow* win, double x, double y)
{
  // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
  int wn_w, wn_h, fb_w, fb_h;
  glfwGetWindowSize(win, &wn_w, &wn_h);
  glfwGetFramebufferSize(win, &fb_w, &fb_h);
  x = x * fb_w / wn_w;
  y = (wn_h - y) * fb_h / wn_h;
  arcball->AccumulateMouseMotion((float)x,(float)y);
}
static void cursorinit (GLFWwindow* win, double x, double y)
{
  // convert screen pos (upside down) to framebuffer pos (e.g., retina displays)
  int wn_w, wn_h, fb_w, fb_h;
  glfwGetWindowSize(win, &wn_w, &wn_h);
  glfwGetFramebufferSize(win, &fb_w, &fb_h);
  x = x * fb_w / wn_w;
  y = (wn_h - y) * fb_h / wn_h;
  arcball->InitMouseMotion((float)x,(float)y);
  glfwSetCursorPosCallback(win, cursorpos);     // cursor position callback
}
static void mousebutton (GLFWwindow* win, int button, int action, int mods)
{
  if (action == GLFW_PRESS) {
    glfwSetCursorPosCallback(win, cursorinit);     // cursor position callback
  }
  else // GLFW_RELEASE 
    glfwSetCursorPosCallback(win, nullptr);      // callback disabled
}

int main ()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
#ifndef _WIN32
  glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER,GLFW_TRUE);  // option for mac os
  //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);       // required for mac os
#endif

  glfwSetErrorCallback(error);

  GLFWwindow* win = glfwCreateWindow(600,400,"Window title",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  glfwSetMouseButtonCallback(win, mousebutton); // mouse button callback
  
  glfwMakeContextCurrent(win);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();

  while(!glfwWindowShouldClose(win)) {
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

