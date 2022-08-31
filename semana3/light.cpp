#include "light.h"

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#else
#include <OpenGL/gl.h>
#endif

int Light::s_id = 0;

Light::Light ()
: m_id(s_id++),   // simple strategy: no reuse of id's
  m_amb{0.2f,0.2f,0.2f,1.0f},
  m_dif{0.8f,0.8f,0.8f,1.0f},
  m_spe{1.0f,1.0f,1.0f,1.0f}
{
}

int Light::GetId ()
{
  return m_id;
}

void Light::SetColor (float r, float g, float b)
{
  m_amb[0] = 0.2f*r;
  m_amb[1] = 0.2f*g;
  m_amb[2] = 0.2f*b;
  m_dif[0] = 0.8f*r;
  m_dif[1] = 0.8f*g;
  m_dif[2] = 0.8f*b;
}

void Light::Setup ()
{
  glEnable(GL_LIGHT0+GetId());
  glLightfv(GL_LIGHT0+GetId(),GL_AMBIENT,m_amb);
  glLightfv(GL_LIGHT0+GetId(),GL_DIFFUSE,m_dif);
  glLightfv(GL_LIGHT0+GetId(),GL_SPECULAR,m_spe);
}