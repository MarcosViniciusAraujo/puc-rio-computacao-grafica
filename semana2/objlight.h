#ifndef OBJLIGHT_H
#define OBJLIGHT_H

#include "light.h"

class ObjLight : public Light {
  float m_pos[4];
public:
  ObjLight (float x, float y, float z, float w=1.0f);
  ~ObjLight ();
  void SetPosition (float x, float y, float z, float w=1.0f);
  virtual void Setup ();
};

#endif