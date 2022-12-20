
#include <GL/gl.h>
#include <GLUT/glut.h>

#include "arcball.h"
#include "camera.h"
#include "objlight.h"
#include "material.h"
#include "transform.h"
#include "cube.h"
#include "sphere.h"

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.0f, 4.0f};

static Camera* camera;
static Arcball* arcball;
static Light* light;
static Material* red;
static Material* gray;
static Transform* trf1;
static Transform* trf2;
static Cube* cube;
static Sphere* sphere;

static void initialize (void)
{
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
  red = new Material(1.0f,0.0f,0.0f);
  gray = new Material(0.8f,0.8f,0.8f);
  trf1 = new Transform();
  trf1->Translate(0.0f,0.5f,0.0f);
  trf1->Scale(0.5f,0.5f,0.5f);
  trf2 = new Transform();
  trf2->Scale(2.0f,0.2f,2.0f);
  trf2->Translate(0.0f,-1.0f,0.0f);
  cube = new Cube();
  sphere = new Sphere();
}

static void display (void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  camera->Setup();
  light->Setup();
  //trf1->Load();
  red->Load();
  cube->Draw();
  //trf1->Unload();
  gray->Load();
  trf2->Load();
  cube->Draw();
  trf2->Unload();
  glutSwapBuffers(); // update screen 
}

static void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
    case 'x':
      viewer_pos[0] *= -1;
    break;
    case 'y':
      viewer_pos[1] *= -1;
    break;
    case 'z':
      viewer_pos[2] *= -1;
    break;
    case 'q':
      exit(0);
    break;
  }
  glutPostRedisplay();
}

static void motion (int x, int y)
{
  int vp[4];  // viewport dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,vp);  
  arcball->AccumulateMouseMotion((float)x,(float)(vp[3]-y));
  glutPostRedisplay();
}

static void mouse (int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) { 
    int vp[4];  // viewport dimension: {x0, y0, w, h} 
    glGetIntegerv(GL_VIEWPORT,vp);  
    arcball->InitMouseMotion((float)x,(float)(vp[3]-y));
    glutMotionFunc(motion);
  }
  else {
    glutMotionFunc(0);
  }
}

int main (int argc, char* argv[])
{
  // open GLUT 
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
  glutInitWindowSize (600, 400); 

  // create window 
  glutCreateWindow ("simple");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard); 
  glutMouseFunc(mouse);

  // enter interaction 
  initialize();
  glutMainLoop();
  return 0;
}

