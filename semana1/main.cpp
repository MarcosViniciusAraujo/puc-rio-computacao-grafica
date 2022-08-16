#include <GL/gl.h>
#include <GLUT/glut.h>

#include <iostream>

static float viewer_pos[3] = {2.0f, 3.0f, 4.0f};

static void initialize (void)
{
  // set background color: white 
  glClearColor(1.0f,1.0f,1.0f,1.0f);
  // enable depth test 
  glEnable(GL_DEPTH_TEST);
  // enable lighting computation 
  glEnable(GL_LIGHTING);
  // enable light source number 0 
  glEnable(GL_LIGHT0);
  // enable normalization of normal vectors 
  glEnable(GL_NORMALIZE);
}

static void drawCube (void)
{
  // draw cube of size 1.0 with origin at the base midpoint
  glBegin(GL_QUADS);

    // back face: counter clockwise 
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glVertex3f(-0.5f, 0.0f,-0.5f);
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glVertex3f(-0.5f, 1.0f,-0.5f);
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glVertex3f( 0.5f, 1.0f,-0.5f);
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glVertex3f( 0.5f, 0.0f,-0.5f);

    // front face: counter clockwise 
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, 0.0f, 0.5f);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f( 0.5f, 1.0f, 0.5f);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, 1.0f, 0.5f);

    // left face: counter clockwise 
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f,-0.5f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 1.0f, 0.5f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, 1.0f,-0.5f);

    // right face: counter clockwise 
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.5f, 0.0f,-0.5f);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.5f, 1.0f,-0.5f);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.5f, 1.0f, 0.5f);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( 0.5f, 0.0f, 0.5f);

    // botton face: counter clockwise 
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f,-0.5f);
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f( 0.5f, 0.0f,-0.5f);
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f( 0.5f, 0.0f, 0.5f);
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.5f);

    // top face: counter clockwise 
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 1.0f,-0.5f);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 1.0f, 0.5f);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, 1.0f, 0.5f);
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 0.5f, 1.0f,-0.5f);

  glEnd();
}



// setup camera
static void setCamera (void)
{
  int viewport[4];  // viewport dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,viewport);  
  float ratio = (float) viewport[2] / viewport[3];

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, ratio, 1.0f, 10.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(viewer_pos[0],viewer_pos[1],viewer_pos[2],  // camera position 
            0.0f,0.0f,0.0f,                             // scene center: "look at" 
            0.0f,1.0f,0.0f                              // camera up vector 
           );
}

static void drawCube1 ()
{
  drawCube();
}

static void drawCube2 ()
{
  glPushMatrix();
  glScalef(2.0f,0.2f,2.0f);
  glTranslatef(0.0f,-1.0f,0.0f);
  drawCube();
  glPopMatrix();
}

static void drawCube3 ()
{
  glPushMatrix();
  glScalef(0.7f,0.7f,0.7f);
  glTranslatef(0.0f,1.35f,0.0f);
  drawCube();
  glPopMatrix();
}

// define light source 
static void setLight (void)
{
  float amb[] = {0.1f,0.1f,0.1f,1.0f};
  float dif[] = {0.7f,0.7f,0.7f,1.0f};
  glLightfv(GL_LIGHT0,GL_POSITION,viewer_pos);
  glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
}

// define material 
static void loadMaterialRed ()
{
  float red[] = {1.0f,0.0f,0.0f,1.0f};
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,red);
} 
static void loadMaterialGray ()
{
  float gray[] = {0.8f,0.8f,0.8f,1.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,gray);
} 
 
static void loadMaterialBlue ()
{
  float b[] = {0.0f,0.0f,1.0f,1.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,b);
} 

static void display (void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window 
  setCamera();
  setLight();
  loadMaterialRed();
  drawCube1();
  loadMaterialGray();
  drawCube2();
  loadMaterialBlue();
  drawCube3();
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

  // enter interaction 
  initialize();
  glutMainLoop();
  return 0;
}
