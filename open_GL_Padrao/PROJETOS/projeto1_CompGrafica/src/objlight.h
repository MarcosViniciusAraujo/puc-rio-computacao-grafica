#include <memory>
class ObjLight;
typedef std::shared_ptr<ObjLight> ObjLightPtr;

#ifndef OBJLIGHT_H
#define OBJLIGHT_H

#include "light.h"

class ObjLight : public Light {
  float m_pos[4];
protected:
  ObjLight (float x=0, float y=0, float z=0, float w=1.0f);
public:
  static ObjLightPtr Make (float x, float y, float z, float w=1.0f);
  virtual ~ObjLight ();
  void SetPosition (float x, float y, float z, float w=1.0f);
  virtual int Setup () const;
};

#endif