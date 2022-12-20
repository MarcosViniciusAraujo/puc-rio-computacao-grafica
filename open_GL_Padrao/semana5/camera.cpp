#include "camera.h"
#include "arcball.h"

#include <cmath>
#include <iostream>

#include <GL/gl.h>
#include <GLUT/glut.h>  // glu functions

#define PI 3.14159265f
#define TO_RAD(a) ((a)*PI/180.0f)

static bool InvertMatrix(const float m[16], float invOut[16]);

Camera::Camera (float eyex, float eyey, float eyez, 
                float centerx, float centery, float centerz,
                float upx, float upy, float upz)
: m_ortho(false),
  m_fovy(50.0f), m_znear(0.1f), m_zfar(100.0f),
  m_eye{eyex,eyey,eyez},
  m_center{centerx,centery,centerz},
  m_up{upx,upy,upz},
  m_arcball(nullptr),
  m_reference(nullptr)
{
}

CameraPtr Camera::Make (float eyex, float eyey, float eyez, 
                        float centerx, float centery, float centerz,
                        float upx, float upy, float upz)
{
  return CameraPtr(new Camera(eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz));
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

void Camera::SetOrtho (bool ortho)
{
  m_ortho = ortho;
}

void Camera::SetReference (NodePtr reference)
{
  m_reference = reference;
}

ArcballPtr Camera::CreateArcball ()
{
  float distance = sqrt(
      (m_eye[0] - m_center[0])*(m_eye[0] - m_center[0]) +
      (m_eye[1] - m_center[1])*(m_eye[1] - m_center[1]) +
      (m_eye[2] - m_center[2])*(m_eye[2] - m_center[2])
    );
  m_arcball = Arcball::Make(distance);
  return m_arcball;
}

void Camera::Setup () const
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
  if (m_reference) {
    float mat[16], inv[16];
    m_reference->GetModelMatrix(mat);
    InvertMatrix(mat,inv);
    glMultMatrixf(inv);
  }
}

// From MESA implementation
static bool InvertMatrix(const float m[16], float invOut[16])
{
  float inv[16], det;
  int i;
  inv[0] = m[5]  * m[10] * m[15] - 
            m[5]  * m[11] * m[14] - 
            m[9]  * m[6]  * m[15] + 
            m[9]  * m[7]  * m[14] +
            m[13] * m[6]  * m[11] - 
            m[13] * m[7]  * m[10];
  inv[4] = -m[4]  * m[10] * m[15] + 
            m[4]  * m[11] * m[14] + 
            m[8]  * m[6]  * m[15] - 
            m[8]  * m[7]  * m[14] - 
            m[12] * m[6]  * m[11] + 
            m[12] * m[7]  * m[10];

  inv[8] = m[4]  * m[9] * m[15] - 
            m[4]  * m[11] * m[13] - 
            m[8]  * m[5] * m[15] + 
            m[8]  * m[7] * m[13] + 
            m[12] * m[5] * m[11] - 
            m[12] * m[7] * m[9];
  inv[12] = -m[4]  * m[9] * m[14] + 
              m[4]  * m[10] * m[13] +
              m[8]  * m[5] * m[14] - 
              m[8]  * m[6] * m[13] - 
              m[12] * m[5] * m[10] + 
              m[12] * m[6] * m[9];
  inv[1] = -m[1]  * m[10] * m[15] + 
            m[1]  * m[11] * m[14] + 
            m[9]  * m[2] * m[15] - 
            m[9]  * m[3] * m[14] - 
            m[13] * m[2] * m[11] + 
            m[13] * m[3] * m[10];
  inv[5] = m[0]  * m[10] * m[15] - 
            m[0]  * m[11] * m[14] - 
            m[8]  * m[2] * m[15] + 
            m[8]  * m[3] * m[14] + 
            m[12] * m[2] * m[11] - 
            m[12] * m[3] * m[10];
  inv[9] = -m[0]  * m[9] * m[15] + 
            m[0]  * m[11] * m[13] + 
            m[8]  * m[1] * m[15] - 
            m[8]  * m[3] * m[13] - 
            m[12] * m[1] * m[11] + 
            m[12] * m[3] * m[9];
  inv[13] = m[0]  * m[9] * m[14] - 
            m[0]  * m[10] * m[13] - 
            m[8]  * m[1] * m[14] + 
            m[8]  * m[2] * m[13] + 
            m[12] * m[1] * m[10] - 
            m[12] * m[2] * m[9];
  inv[2] = m[1]  * m[6] * m[15] - 
            m[1]  * m[7] * m[14] - 
            m[5]  * m[2] * m[15] + 
            m[5]  * m[3] * m[14] + 
            m[13] * m[2] * m[7] - 
            m[13] * m[3] * m[6];
  inv[6] = -m[0]  * m[6] * m[15] + 
            m[0]  * m[7] * m[14] + 
            m[4]  * m[2] * m[15] - 
            m[4]  * m[3] * m[14] - 
            m[12] * m[2] * m[7] + 
            m[12] * m[3] * m[6];
  inv[10] = m[0]  * m[5] * m[15] - 
            m[0]  * m[7] * m[13] - 
            m[4]  * m[1] * m[15] + 
            m[4]  * m[3] * m[13] + 
            m[12] * m[1] * m[7] - 
            m[12] * m[3] * m[5];
  inv[14] = -m[0]  * m[5] * m[14] + 
              m[0]  * m[6] * m[13] + 
              m[4]  * m[1] * m[14] - 
              m[4]  * m[2] * m[13] - 
              m[12] * m[1] * m[6] + 
              m[12] * m[2] * m[5];
  inv[3] = -m[1] * m[6] * m[11] + 
            m[1] * m[7] * m[10] + 
            m[5] * m[2] * m[11] - 
            m[5] * m[3] * m[10] - 
            m[9] * m[2] * m[7] + 
            m[9] * m[3] * m[6];
  inv[7] = m[0] * m[6] * m[11] - 
            m[0] * m[7] * m[10] - 
            m[4] * m[2] * m[11] + 
            m[4] * m[3] * m[10] + 
            m[8] * m[2] * m[7] - 
            m[8] * m[3] * m[6];
  inv[11] = -m[0] * m[5] * m[11] + 
              m[0] * m[7] * m[9] + 
              m[4] * m[1] * m[11] - 
              m[4] * m[3] * m[9] - 
              m[8] * m[1] * m[7] + 
              m[8] * m[3] * m[5];
  inv[15] = m[0] * m[5] * m[10] - 
            m[0] * m[6] * m[9] - 
            m[4] * m[1] * m[10] + 
            m[4] * m[2] * m[9] + 
            m[8] * m[1] * m[6] - 
            m[8] * m[2] * m[5];
  det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
  if (det == 0)
      return false;
  det = 1.0 / det;
  for (i = 0; i < 16; i++)
      invOut[i] = inv[i] * det;
  return true;
}