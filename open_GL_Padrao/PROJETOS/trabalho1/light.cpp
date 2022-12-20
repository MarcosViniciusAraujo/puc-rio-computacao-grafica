#include "light.h"

#include <GL/gl.h>

int Light::s_id = 0;

Light::Light ()
: m_id(s_id++),   // simple strategy: no reuse of id's
  m_amb{0.2f,0.2f,0.2f,1.0f},
  m_dif{0.8f,0.8f,0.8f,1.0f},
  m_spe{1.0f,1.0f,1.0f,1.0f}
{
}

Light::~Light ()
{
}

int Light::GetId () const
{
  return m_id;
}

void Light::SetAmbient (float r, float g, float b)
{
  m_amb[0] = r;
  m_amb[1] = g;
  m_amb[2] = b;
}

void Light::SetDiffuse (float r, float g, float b)
{
  m_dif[0] = r;
  m_dif[1] = g;
  m_dif[2] = b;
}

void Light::SetSpecular (float r, float g, float b)
{
  m_spe[0] = r;
  m_spe[1] = g;
  m_spe[2] = b;
}

void Light::SetReference (NodePtr reference)
{
  m_reference = reference;
}

NodePtr Light::GetReference () const
{
  return m_reference;
}

int Light::Setup () const
{
  glEnable(GL_LIGHT0+GetId());
  glLightfv(GL_LIGHT0+GetId(),GL_AMBIENT,m_amb);
  glLightfv(GL_LIGHT0+GetId(),GL_DIFFUSE,m_dif);
  glLightfv(GL_LIGHT0+GetId(),GL_SPECULAR,m_spe);
  return 1;
}