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

static void display (void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  scene->Render(camera);
  glutSwapBuffers(); // update screen 
}

static void specialkeyboard (int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_UP:
      engine->SetSpeedFactor(engine->GetSpeedFactor() * 1.1f);
    break;
    case GLUT_KEY_DOWN:
      engine->SetSpeedFactor(engine->GetSpeedFactor() / 1.1f);
    break;
  }
}

static void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
    case 'g':
      camera = Camera::Make(0.0f, 0.0f, 10.0f);
      staring_the_moon = false;
    break;
    case 'h':
      camera = Camera::Make(0.0f,0.0f,0.0f,1.0f,0.0f,0.0f);
      camera->SetReference(g_earth);
      //camera->SetUpDir(0.0f,-1.0f,0.0f);
      staring_the_moon = false;
    break;
    case 'i':
      camera = Camera::Make(0.0f, 0.0f, 10.0f);
      //camera->SetUpDir(0.0f,-1.0f,0.0f);
      staring_the_moon = true;
    break;
    case 'q':
      exit(0);
    break;
  }
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

static void update (void) 
{
  static float t0 = 0;
  float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
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
  glutPostRedisplay();
}

int main (int argc, char* argv[])
{
  // open GLUT 
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
  glutInitWindowSize (800, 400); 

  // create window 
  glutCreateWindow ("Mini solar system");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard); 
  glutSpecialFunc(specialkeyboard); 
  glutMouseFunc(mouse);
  glutIdleFunc(update);

  // enter interaction 
  initialize();
  glutMainLoop();
  return 0;
}

