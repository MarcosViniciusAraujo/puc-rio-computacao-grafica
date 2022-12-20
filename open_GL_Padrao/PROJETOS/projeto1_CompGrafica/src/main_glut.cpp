#include <GL/gl.h>
#include <GLUT/glut.h>

#include "arcball.h"
#include "scene.h"
#include "camera.h"
#include "objlight.h"
#include "material.h"
#include "transform.h"
#include "cube.h"
#include "cube_array.h"
#include "sphere.h"

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.5f, 4.0f};

static ScenePtr scene;
static CameraPtr camera;
static ArcballPtr arcball;

static void initialize (void)
{
  // set background color: white 
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);

  // create objects
  camera = Camera::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  LightPtr light = ObjLight::Make(viewer_pos[0],viewer_pos[1],viewer_pos[2]);
  MaterialPtr red = Material::Make(1.0f,0.0f,0.0f);
  MaterialPtr gray = Material::Make(0.8f,0.8f,0.8f);
  TransformPtr trf1 = Transform::Make();
  trf1->Translate(0.0f,0.5f,0.0f);
  trf1->Scale(0.5f,0.5f,0.5f);
  TransformPtr trf2 = Transform::Make();
  trf2->Scale(2.0f,0.2f,2.0f);
  trf2->Translate(0.0f,-1.0f,0.0f);
  ShapePtr cube = CubeArray::Make();
  ShapePtr sphere = Sphere::Make();

  // build scene
  NodePtr root = Node::Make(
    {Node::Make(trf1,{red},{sphere}),
     Node::Make(trf2,{gray},{cube})
    }
  );
  arcball = camera->CreateArcball();
  scene = Scene::Make(root,light);
}

static void display (void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  scene->Render(camera);
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
  arcball->AccumulateMouseMotion(x,vp[3]-y);
  glutPostRedisplay();
}

static void mouse (int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) { 
    int vp[4];  // viewport dimension: {x0, y0, w, h} 
    glGetIntegerv(GL_VIEWPORT,vp);  
    arcball->InitMouseMotion(x,vp[3]-y);
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

