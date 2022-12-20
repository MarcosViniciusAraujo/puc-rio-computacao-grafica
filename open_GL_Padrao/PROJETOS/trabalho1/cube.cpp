#include "cube.h"

#include <GL/gl.h>

Cube::Cube ()
{
}

CubePtr Cube::Make ()
{
  return CubePtr(new Cube());
}

Cube::~Cube () 
{
}

void Cube::Draw ()
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