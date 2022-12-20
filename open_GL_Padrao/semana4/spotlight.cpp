#include "spotlight.h"

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#else
#include <OpenGL/gl.h>
#endif

Spotlight::Spotlight (float x, float y, float z, float w, GLfloat xD, 
GLfloat yD, GLfloat zD, GLfloat angle, GLfloat concentracao)
: m_pos{x,y,z,w}, m_direct{xD, yD, zD}, angulo(angle), concentracao(concentracao)
{
}

Spotlight::~Spotlight ()
{
}

void Spotlight::SetPosition (float x, float y, float z, float w)
{
  m_pos[0] = x;
  m_pos[1] = y;
  m_pos[2] = z;
  m_pos[3] = w;
}

void Spotlight::SetDirect(GLfloat xD, GLfloat yD, GLfloat zD){
  m_direct[0] = xD;
  m_direct[1] = yD;
  m_direct[2] = zD;
}

void Spotlight::Setup ()
{
  Light::Setup();
  Light::SetColor(0.0f, 1.0f, 0.0f);
  glLightfv(GL_LIGHT0+GetId(),GL_POSITION,m_pos);
  glLightfv(GL_LIGHT0+GetId(),GL_SPOT_DIRECTION, m_direct);
  glLightf(GL_LIGHT0+GetId(),GL_SPOT_EXPONENT, concentracao);
  glLightf(GL_LIGHT0+GetId(),GL_LINEAR_ATTENUATION, 2);
  glLightf(GL_LIGHT0+GetId(),GL_SPOT_CUTOFF, angulo);  

}