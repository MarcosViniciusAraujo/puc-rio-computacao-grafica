#include "arcball.h"

#include <GL/gl.h>
#include <cmath>
#include <iostream>

#define PI 3.14159265

// Map function: from screen (x,y) to unit sphere (px,py,pz)
static void Map (int width, int height, int x, int y, float* px, float* py, float* pz)
{
  float r = width < height ? width/2.0f : height/2.0f;
  float X = (x - width/2.0f) / r;
  float Y = (y - height/2.0f) / r;
  float Z;
  float l = sqrt(X*X + Y*Y);
  if (l <= 1.0f) {
    Z = sqrt(1.0f - l*l);
  }
  else {
    X /= l;
    Y /= l;
    Z = 0.0f;
  }
  *px = X;
  *py = Y;
  *pz = Z;
}

Arcball::Arcball (float distance) 
: m_distance(distance), m_x0(0), m_y0(0)
{
  // set identity as initial value 
  for (int i=0; i<16; ++i)
    m_mat[i] = i%5 == 0 ? 1.0f : 0.0f;
}

ArcballPtr Arcball::Make (float distance)
{
  return ArcballPtr(new Arcball(distance));
}

void Arcball::setZoom (float x)
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-m_distance);
  glScalef(x, x, x);
  glTranslatef(0.0f,0.0f,m_distance);
  glMultMatrixf(m_mat);
  glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
  glPopMatrix();
}


void Arcball::InitMouseMotion (int x0, int y0)
{
  m_x0 = x0;
  m_y0 = y0;
}

void Arcball::AccumulateMouseMotion (int x, int y)
{
  int vp[4];  // vp dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,vp);  
  float ux, uy, uz;
  float vx, vy, vz;
  Map(vp[2],vp[3],m_x0,m_y0,&ux,&uy,&uz);
  Map(vp[2],vp[3],x,y,&vx,&vy,&vz);
  m_x0 = x;
  m_y0 = y;
  float ax = uy*vz - uz*vy;
  float ay = uz*vx - ux*vz;
  float az = ux*vy - uy*vx;
  float theta = 2*asin(sqrt(ax*ax+ay*ay+az*az)); 
  // m_mat = T * R * T
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-m_distance);
  glRotatef(theta*180.0f/PI,ax,ay,az);
  glTranslatef(0.0f,0.0f,m_distance);
  glMultMatrixf(m_mat);
  glGetFloatv(GL_MODELVIEW_MATRIX, m_mat);
  glPopMatrix();
}

const float* Arcball::GetMatrix () const
{
  return m_mat;
}
