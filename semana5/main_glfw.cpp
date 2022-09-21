#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#include <GLFW/glfw3.h>
#else
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#endif

#include "arcball.h"
#include "scene.h"
#include "camera.h"
#include "objlight.h"
#include "material.h"
#include "transform.h"
#include "cube.h"
#include "cube_array.h"
#include "sphere.h"
#include "pyramid_array.h"

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.5f, 4.0f};

static ScenePtr scene;
static CameraPtr camera;
static ArcballPtr arcball;

static void initialize (void)
{
  // set background color: white 
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);

  // create objects
  camera = Camera::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  LightPtr light = ObjLight::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);

  //materiais
  MaterialPtr red = Material::Make(1.0f,0.0f,0.0f);
  MaterialPtr blue = Material::Make(0.0f,0.0f,1.0f);
  MaterialPtr yellow = Material::Make(1.0f,1.0f,0.2f);
  MaterialPtr gray = Material::Make(0.8f,0.8f,0.8f);

  // transformações
  TransformPtr trfCubo = Transform::Make();
  trfCubo->Scale(0.5f, 0.5f, 0.5f);



    //-> Mesa
  TransformPtr trfTampao = Transform::Make();
  trfTampao->Scale(3.0f, 0.2f, 3.0f);
  trfTampao->Translate(0.0f, -1.0f, 0.0f);

  TransformPtr trfPerna1 = Transform::Make();
  trfPerna1->Translate(-1.4f, -1.5f, -1.4f);
  trfPerna1->Scale(0.2f, 1.5f, 0.2f);

  TransformPtr trfPerna2 = Transform::Make();
  trfPerna2->Translate(-1.4f, -1.5f, 1.4f);
  trfPerna2->Scale(0.2f, 1.5f, 0.2f);

  TransformPtr trfPerna3 = Transform::Make();
  trfPerna3->Translate(1.4f, -1.5f, -1.4f);
  trfPerna3->Scale(0.2f, 1.5f, 0.2f);

  TransformPtr trfPerna4 = Transform::Make();
  trfPerna4->Translate(1.4f, -1.5f, 1.4f);
  trfPerna4->Scale(0.2f, 1.5f, 0.2f);



    //-> Piramide
  TransformPtr trfPiramide = Transform::Make();
  trfPiramide->Translate(0.8f, 0.0f, -1.0f);
  trfPiramide->Scale(0.7f, 0.7f, 0.7f);




    //->lampada
  
  TransformPtr trfBaseLamp = Transform::Make();
  trfBaseLamp->Translate(-0.8f, 0.0f, 1.0f);
  trfBaseLamp->Scale(0.5f, 0.1f, 0.5f);

  TransformPtr trfCaboLamp = Transform::Make();
  trfCaboLamp->Translate(-0.8f, 0.0f, 1.0f);
  trfCaboLamp->Rotate(15.0f, 1.0f, 0.0f, 0.0f);
  trfCaboLamp->Rotate(45.0f, 0.0f, 1.0f, 0.0f);
  trfCaboLamp->Scale(0.1f, 1.0f, 0.1f);


  TransformPtr trfArticulacaoLamp = Transform::Make();
  trfArticulacaoLamp->Translate(-0.80f, 1.0f, 1.25f);
  trfArticulacaoLamp->Scale(0.11f, 0.11f, 0.11f);


  TransformPtr trfCabo2Lamp = Transform::Make();
  //trfCabo2Lamp->Translate();
  //trfCabo2Lamp->Scale();

  //shapes
  ShapePtr tampao = CubeArray::Make();
  ShapePtr cube = CubeArray::Make();
  ShapePtr perna = CubeArray::Make();
  ShapePtr piramide = PyramidArray::Make();

  ShapePtr baseLamp = CubeArray::Make();
  ShapePtr CaboLamp = CubeArray::Make();
  ShapePtr articulacaoLamp = Sphere::Make();
  ShapePtr cabecaLamp = PyramidArray::Make();


  //build scene
  
  NodePtr root = Node::Make(
    {
      //Node::Make(trfCubo, {yellow}, {cube}),
      Node::Make(trfTampao, {gray}, {tampao}),
      Node::Make(trfPiramide, {yellow}, {piramide}),
      Node::Make(trfPerna1, {gray}, {perna}),
      Node::Make(trfPerna2, {gray}, {perna}),
      Node::Make(trfPerna3, {gray}, {perna}),
      Node::Make(trfPerna4, {gray}, {perna}),
      Node::Make(trfBaseLamp, {blue}, {baseLamp}),
      Node::Make(trfCaboLamp, {gray}, {CaboLamp}),
      Node::Make(trfArticulacaoLamp, {yellow}, {articulacaoLamp}),
      Node::Make(trfCabo2Lamp, {red}, {CaboLamp}),
    }

  );


  arcball = camera->CreateArcball();
  scene = Scene::Make(root,light);
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
  scene->Render(camera);
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
