#ifndef CAMERA_H
#define CAMERA_H

#include "arcball.h"

class Camera {
  float m_ortho;
  float m_fovy;
  float m_znear, m_zfar;
  float m_center[3];
  float m_eye[3];   
  float m_up[3];   
  Arcball* m_arcball;
public:
  Camera (float x, float y, float z);
  ~Camera ();
  void SetAngle (float fovy);
  void SetZPlanes (float near, float far);
  void SetCenter (float x, float y, float z);
  void SetEye (float x, float y, float z);
  void SetUpDir (float x, float y, float z);
  void SetOrtho (bool ortho);
  Arcball* CreateArcball ();
  void Setup ();
};

#endif