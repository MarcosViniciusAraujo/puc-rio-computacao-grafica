#include "material.h"

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#else
#include <OpenGL/gl.h>
#endif

Material::Material (float r, float g, float b)
: m_amb{r,g,b,1.0f}, m_dif{r,g,b,1.0f}, 
  m_spe{1.0f,1.0f,1.0f,1.0f}, m_shi(90.0f)
{
}
Material::~Material ()
{
}
void Material::SetAmbient (float r, float g, float b)
{
  m_amb[0] = r;
  m_amb[1] = r;
  m_amb[2] = b;
}
void Material::SetDiffuse (float r, float g, float b)
{
  m_dif[0] = r;
  m_dif[1] = r;
  m_dif[2] = b;
}
void Material::SetSpecular (float r, float g, float b)
{
  m_spe[0] = r;
  m_spe[1] = r;
  m_spe[2] = b;
}
void Material::SetShininess (float shi)
{
  m_shi = shi;
}
void Material::Load ()
{
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_amb);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_dif);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,m_spe);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m_shi);
}
