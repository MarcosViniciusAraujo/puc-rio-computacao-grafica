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
#include "solar_syst.h"

#include <iostream>


const float sun_size = 1.0f;
const float earth_size = 0.6f;
const float moon_size = 0.2f;
const float earth_distance = 8.0f;
const float moon_distance = 2.0f;

static ScenePtr scene;
static CameraPtr camera;
static ArcballPtr arcball;
static SolarSystPtr engine;

static bool staring_the_moon = false;
static NodePtr g_earth, g_moon;

static void initialize (void)
{
  // set background color: white 
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);
  // do not draw back faces
  glEnable(GL_CULL_FACE);

  // create objects
  LightPtr light = ObjLight::Make(0.0f,0.0f,0.0f);
  light->SetAmbient(1.0f,1.0f,1.0f);
  // materials
  MaterialPtr sMat = Material::Make(1.0f,0.6f,0.2f);
  sMat->SetAmbient(1.0f,0.6f,0.2f);
  MaterialPtr eMat = Material::Make(0.2f,0.2f,1.0f);
  eMat->SetAmbient(0.0f,0.0f,0.0f);
  eMat->SetSpecular(0.0f,0.0,0.0f);
  eMat->SetShininess(16.0f);
  MaterialPtr mMat = Material::Make(0.9f,0.9f,0.9f);
  mMat->SetAmbient(0.0f,0.0f,0.0f);
  mMat->SetSpecular(0.0f,0.0f,0.0f);
  // sun transforms
  TransformPtr sS = Transform::Make(); sS->Scale(-sun_size,-sun_size,-sun_size); // flip faces to iluminate
  // earth transforms
  TransformPtr eT = Transform::Make();
  TransformPtr eD = Transform::Make(); eD->Translate(earth_distance,0.0f,0.0f);
  TransformPtr eR = Transform::Make();
  TransformPtr eS = Transform::Make(); eS->Scale(earth_size,earth_size,earth_size);
  // moon transforms
  TransformPtr mT = Transform::Make();
  TransformPtr mD = Transform::Make(); mD->Translate(moon_distance,0.0f,0.0f);
  TransformPtr mS = Transform::Make(); mS->Scale(moon_size,moon_size,moon_size);
  // geometry
  ShapePtr sphere = Sphere::Make();

  // build scene
  NodePtr moon_node = Node::Make(mS,{mMat},{sphere});
  NodePtr earth_node = Node::Make(eS,{eMat},{sphere});
  NodePtr sun_node = Node::Make(sS,{sMat},{sphere});
  NodePtr eR_node = Node::Make(eR,{earth_node}); g_earth = eR_node;
  NodePtr mD_node = Node::Make(mD,{moon_node}); g_moon = mD_node;
  NodePtr mT_node = Node::Make(mT,{mD_node});
  NodePtr eD_node = Node::Make(eD,{eR_node,mT_node});
  NodePtr eT_node = Node::Make(eT,{eD_node});
  NodePtr root = Node::Make({sun_node,eT_node});
  scene = Scene::Make(root,light);
  camera = Camera::Make(0.0f, 0.0f, 10.0f);

  arcball = camera->CreateArcball();
  engine = SolarSyst::Make(eR,eT,mT);
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
  switch (key) {
    case GLFW_KEY_UP:
      engine->SetSpeedFactor(engine->GetSpeedFactor() * 1.1f);
    break;
    case GLFW_KEY_DOWN:
      engine->SetSpeedFactor(engine->GetSpeedFactor() / 1.1f);
    break;
    case GLFW_KEY_G:
      //vista do sistema solar
      camera = Camera::Make(0.0f, 0.0f, 10.0f);
      staring_the_moon = false;
    break;
    case GLFW_KEY_H:
      //vista de um ser humano no hemisferio sul
      camera = Camera::Make(0.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
      camera->SetReference(g_earth);
      camera->SetUpDir(0.0f,-1.0f,0.0f);
      staring_the_moon = false;
    break;
    case GLFW_KEY_I:
      camera = Camera::Make(0.0f, 0.0f, 10.0f);
      camera->SetUpDir(0.0f,-1.0f,0.0f);
      staring_the_moon = true;
    break;
    case GLFW_KEY_Q:
      exit(0);
    break;
  }
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

static void update (void) 
{
  static float t0 = 0;
  float t = glfwGetTime();  // in seconds
  float dt = (t - t0);
  scene->Update(dt);
  t0 = t;
  if (staring_the_moon) {
    float m[16];
    g_earth->GetModelMatrix(m);
    camera->SetEye(m[12],m[13],m[14]);
    g_moon->GetModelMatrix(m);
    camera->SetCenter(m[12],m[13],m[14]);
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

  GLFWwindow* win = glfwCreateWindow(800,400,"Mini solar system",nullptr,nullptr);
  glfwSetFramebufferSizeCallback(win, resize);  // resize callback
  glfwSetKeyCallback(win, keyboard);            // keyboard callback
  glfwSetMouseButtonCallback(win, mousebutton); // mouse button callback
  
  glfwMakeContextCurrent(win);
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));

  initialize();

  while(!glfwWindowShouldClose(win)) {
    update();
    display(win);
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
