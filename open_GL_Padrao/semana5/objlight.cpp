#include "objlight.h"

#include <GL/gl.h>

ObjLight::ObjLight (float x, float y, float z, float w)
: m_pos{x,y,z,w}
{
}

ObjLightPtr ObjLight::Make (float x, float y, float z, float w)
{
   return ObjLightPtr(new ObjLight(x,y,z,w));
}

ObjLight::~ObjLight ()
{
}

void ObjLight::SetPosition (float x, float y, float z, float w)
{
  m_pos[0] = x;
  m_pos[1] = y;
  m_pos[2] = z;
  m_pos[3] = w;
}

int ObjLight::Setup () const
{
  Light::Setup();
  if (GetReference()) {
    float mat[16];
    GetReference()->GetModelMatrix(mat);
    glPushMatrix();
    glMultMatrixf(mat);
  }
  glLightfv(GL_LIGHT0+GetId(),GL_POSITION,m_pos);
  if (GetReference()) {
    glPopMatrix();
  }
  return 1;
}