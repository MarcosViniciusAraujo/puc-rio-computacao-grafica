#include "objlight.h"

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#else
#include <OpenGL/gl.h>
#endif

ObjLight::ObjLight (float x, float y, float z, float w)
: m_pos{x,y,z,w}
{
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

void ObjLight::Setup ()
{
  Light::Setup();
  glLightfv(GL_LIGHT0+GetId(),GL_POSITION,m_pos);
}