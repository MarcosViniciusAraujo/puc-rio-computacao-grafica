#include "camera.h"
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif


#define PI 3.14159265f
#define TO_RAD(a) ((a)*PI/180.0f)

Camera::Camera (float x, float y, float z)
: m_ortho(false),
  m_fovy(50.0f), m_znear(0.1f), m_zfar(100.0f),
  m_center{0.0f,0.0f,0.0f},
  m_eye{x,y,z},
  m_up{0.0f,1.0f,0.0f},
  m_arcball(nullptr)
{
}

Camera::~Camera ()
{
}

void Camera::SetAngle (float fovy)
{
  m_fovy = fovy;
}

void Camera::SetZPlanes (float znear, float zfar)
{
  m_znear = znear;
  m_zfar = zfar;
}

void Camera::SetCenter (float x, float y, float z)
{
  m_center[0] = x;
  m_center[1] = y;
  m_center[2] = z;
}

void Camera::SetEye (float x, float y, float z)
{
  m_eye[0] = x;
  m_eye[1] = y;
  m_eye[2] = z;
}

void Camera::SetUpDir (float x, float y, float z)
{
  m_up[0] = x;
  m_up[1] = y;
  m_up[2] = z;
}

Arcball* Camera::CreateArcball ()
{
  float distance = sqrt(
      (m_eye[0] - m_center[0])*(m_eye[0] - m_center[0]) +
      (m_eye[1] - m_center[1])*(m_eye[1] - m_center[1]) +
      (m_eye[2] - m_center[2])*(m_eye[2] - m_center[2])
    );
  m_arcball = new Arcball(distance);
  return m_arcball;
}


void Camera::Setup ()
{
    int viewport[4];  // viewport dimension: {x0, y0, w, h} 
  glGetIntegerv(GL_VIEWPORT,viewport);  

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (!m_ortho) {
    float ratio = (float) viewport[2] / viewport[3];
    gluPerspective(m_fovy,ratio,m_znear,m_zfar);
  }
  else {
    float distance = sqrt(
        (m_eye[0] - m_center[0])*(m_eye[0] - m_center[0]) +
        (m_eye[1] - m_center[1])*(m_eye[1] - m_center[1]) +
        (m_eye[2] - m_center[2])*(m_eye[2] - m_center[2])
      );
    float height = distance * tan(TO_RAD(m_fovy)/2.0f);
    float width = height / viewport[3] * viewport[2];
    glOrtho(-width,width,-height,height,m_znear,m_zfar);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (m_arcball) {
    glMultMatrixf(m_arcball->GetMatrix());
  }
  gluLookAt(m_eye[0],m_eye[1],m_eye[2],
            m_center[0],m_center[1],m_center[2],
            m_up[0],m_up[1],m_up[2]
           );
}