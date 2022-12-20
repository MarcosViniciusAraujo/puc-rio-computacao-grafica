#ifndef OBJLIGHT_H
#define OBJLIGHT_H

#include "light.h"

class ObjLight : public Light {
  float m_pos[4];
public:
  ObjLight (float x = 0.0f, float y = 0.0f, float z = 0.0f, float w=1.0f);
  ~ObjLight ();
  void SetPosition (float x, float y, float z, float w=1.0f);
  virtual void Setup ();
};

#endif