#include <memory>
class Camera;
typedef std::shared_ptr<Camera> CameraPtr;

#ifndef CAMERA_H
#define CAMERA_H

#include "arcball.h"
#include "node.h"

class Arcball;

class Camera {
  bool m_ortho;
  float m_fovy;
  float m_znear, m_zfar;
  float m_eye[3];
  float m_center[3];   
  float m_up[3];
  ArcballPtr m_arcball;
  NodePtr m_reference;
protected:
  Camera (float eyex, float eyey, float eyez,
          float centerx, float centery, float centerz,
          float upx, float upy, float upz
         );
public:
  static CameraPtr Make (float eyex, float eyey, float eyez,
                         float centerx=0.0f, float centery=0.0f, float centerz=0.0f,
                         float upx=0.0f, float upy=1.0f, float upz=0.0f
                        );
  virtual ~Camera ();
  void SetAngle (float fovy);
  void SetZPlanes (float near, float far);
  void SetCenter (float x, float y, float z);
  void SetEye (float x, float y, float z);
  void SetUpDir (float x, float y, float z);
  void SetOrtho (bool ortho);
  ArcballPtr CreateArcball ();
  void SetReference (NodePtr reference);
  void Setup () const;
};

#endif