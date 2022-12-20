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
#include "spotlight.h"
#include "tampa_array.h"
#include "engine_pyr.h"
#include <iostream>

static float viewer_pos[3] = {2.0f, 3.5f, 4.0f};
static float viewer_pos2[3] = {-2.0f, -3.5f, -4.0f};

static ScenePtr scene;
static CameraPtr camera;static CameraPtr camera2;
static ArcballPtr arcball;
static ArcballPtr arcball2;
static EnginePyrPtr engine;
static void initialize (void)
{
  // set background color: white 
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);

  // create objects
  camera = Camera::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  camera2 = Camera::Make(viewer_pos2[0],viewer_pos2[1],viewer_pos2[2]);
  LightPtr light = ObjLight::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  light->SetAmbient(0.1f,0.1f,0.1f);
  light->SetDiffuse(0.3f,0.3f,0.1f);
  LightPtr spot = Spotlight::Make(-0.430f, 1.45f, 0.8f, 1.0f, 1.0f, -1.0f, -1.0f, 10.0f, 1);
  //LightPtr spot = Spotlight::Make(0.0f, 0, 0.0f, 0.0f, 0.0f, 0, 0.0f, 0, 0);

  //materiais
  MaterialPtr red = Material::Make(1.0f,0.0f,0.0f);
  MaterialPtr blue = Material::Make(0.0f,0.0f,1.0f);
  MaterialPtr yellow = Material::Make(1.0f,1.0f,0.2f);
  MaterialPtr gray = Material::Make(0.8f,0.8f,0.8f);
  MaterialPtr brownWood = Material::Make(0.38431f,  0.2f,  0.04314f);
  MaterialPtr lightWood = Material::Make(0.52157f,  0.36863f,  0.25882f);
  MaterialPtr darkWood = Material::Make(0.16078f,  0.08627f,  0.01961f);


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
  TransformPtr trfPiramide2 = Transform::Make();trfPiramide2->Scale(0.4f, 0.4f, 0.4f);
  TransformPtr trfPiramideR = Transform::Make();
  




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
  trfArticulacaoLamp->Translate(-0.8f, 1.0f, 1.25f);
  trfArticulacaoLamp->Scale(0.11f, 0.11f, 0.11f);


  TransformPtr trfCabo2Lamp = Transform::Make();
  trfCabo2Lamp->Translate(-0.77f, 1.0f, 1.25f);
  trfCabo2Lamp->Rotate(45.0f, -1.0f, 0.0f, 0.0f);
  trfCabo2Lamp->Rotate(45.0f, 0.0f, 1.0f, 0.0f);
  trfCabo2Lamp->Rotate(30.0f, 1.0f, 0.0f, 0.0f);
  trfCabo2Lamp->Scale(0.1f, 0.6f, 0.1f);


  TransformPtr trfCabecaLamp = Transform::Make();
  trfCabecaLamp->Translate(-0.4f, 1.5f, 0.8f);
  trfCabecaLamp->Rotate(90.0f, 1.0f, -1.0f, 0.0f);
  trfCabecaLamp->Scale(0.5f, 0.5f, 0.5f);


  TransformPtr trfLuzLamp = Transform::Make();
  trfLuzLamp->Translate(-0.430f, 1.45f, 0.8f);
  trfLuzLamp->Scale(0.11f, 0.11f, 0.11f);


  //shapes
  //ShapePtr tampao = CubeArray::Make();
  ShapePtr tampadisc = TampaArray::Make();
  ShapePtr cube = CubeArray::Make();
  ShapePtr perna = CubeArray::Make();
  ShapePtr piramide = PyramidArray::Make();

  ShapePtr baseLamp = CubeArray::Make();
  ShapePtr CaboLamp = CubeArray::Make();
  ShapePtr articulacaoLamp = Sphere::Make();
  ShapePtr cabecaLamp = PyramidArray::Make();
  ShapePtr luzLamp = Sphere::Make();


  //build scene
  NodePtr pyrnode = Node::Make(trfPiramide2, {blue}, {piramide});
  NodePtr root = Node::Make(
    {
      Node::Make(trfTampao, {gray}, {tampadisc}),
      Node::Make(trfPiramideR,{pyrnode}),
      Node::Make(trfPiramide, {yellow}, {piramide}),
      Node::Make(trfPerna1, {gray}, {perna}),
      Node::Make(trfPerna2, {gray}, {perna}),
      Node::Make(trfPerna3, {gray}, {perna}),
      Node::Make(trfPerna4, {gray}, {perna}),
      Node::Make(trfBaseLamp, {brownWood}, {baseLamp}),
      Node::Make(trfCaboLamp, {lightWood}, {CaboLamp}),
      Node::Make(trfArticulacaoLamp, {darkWood}, {articulacaoLamp}),
      Node::Make(trfCabo2Lamp, {lightWood}, {CaboLamp}),
      Node::Make(trfCabecaLamp, {brownWood}, {cabecaLamp}),
      Node::Make(trfLuzLamp, {red}, {luzLamp}),
      //Node::Make(spot),
    }

  );

  
  arcball = camera->CreateArcball();
  arcball2 = camera2->CreateArcball();
  spot->SetAmbient(1.0f,0,0);
  
  scene = Scene::Make(root,spot,light);
  engine = EnginePyr::Make(trfPiramideR);
  scene->AddEngine(engine);
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
  glViewport(0,0,600,600);
  scene->Render(camera);
  glViewport(600,0,600,600);
  scene->Render(camera2);
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
  arcball2->AccumulateMouseMotion((float)x,(float)y);
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
  arcball2->InitMouseMotion((float)x,(float)y);
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
static void update (void) 
{
  static float t0 = 0;
  float t = glfwGetTime();  // in seconds
  float dt = (t - t0);
  scene->Update(dt);
  t0 = t;
}
static void zoom (GLFWwindow* win, double x, double y)
{
  std::cout << y << std::endl;

  if (y < 0){
    //zoom in
    std::cout << "Zoom in de 1.5" << std::endl;
    arcball->setZoom(1.05);
    arcball2->setZoom(1.05);
    
  }

  else{
    //zoom out
    std::cout << "Zoom out de 0.75" << std::endl;
    arcball->setZoom(0.95);
    arcball2->setZoom(0.95);
  }
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

  GLFWwindow* win = glfwCreateWindow(1200,1200,"Window title",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  glfwSetMouseButtonCallback(win, mousebutton); // mouse button callback
  glfwSetScrollCallback(win, zoom);


  glfwMakeContextCurrent(win);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();

  while(!glfwWindowShouldClose(win)) {
    update();
    display(win);
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
