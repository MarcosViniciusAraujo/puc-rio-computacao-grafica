#include "transform.h"
#include <GL/gl.h>
#include <cstring>

Transform::Transform ()
{
  // set identity as initial value 
  for (int i=0; i<16; ++i)
    m_mat[i] = i%5 == 0 ? 1.0f : 0.0f;
}

TransformPtr Transform::Make ()
{
  return TransformPtr(new Transform());
}

Transform::~Transform ()
{
}

void Transform::Translate (float x, float y, float z)
{
  glPushMatrix();
  glLoadMatrixf(m_mat);
  glTranslatef(x,y,z);
  glGetFloatv(GL_MODELVIEW_MATRIX,m_mat);
  glPopMatrix();
}

void Transform::Scale (float x, float y, float z)
{
  glPushMatrix();
  glLoadMatrixf(m_mat);
  glScalef(x,y,z);
  glGetFloatv(GL_MODELVIEW_MATRIX,m_mat);
  glPopMatrix();
}

void Transform::Rotate (float angle, float x, float y, float z)
{
  glPushMatrix();
  glLoadMatrixf(m_mat);
  glRotatef(angle,x,y,z);
  glGetFloatv(GL_MODELVIEW_MATRIX,m_mat);
  glPopMatrix();
}

void Transform::GetMatrix (float mat[6])
{
  memcpy(mat,m_mat,16*sizeof(float));
}

void Transform::Load () const
{
  glPushMatrix();
  glMultMatrixf(m_mat);
}

void Transform::Unload () const
{
  glPopMatrix();
}


