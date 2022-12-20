
#include <memory>
class Material;
typedef std::shared_ptr<Material> MaterialPtr;

#ifndef MATERIAL_H
#define MATERIAL_H

#include "appearance.h"

class Material : public Appearance {
  float m_amb[4]; 
  float m_dif[4]; 
  float m_spe[4];
  float m_shi;
protected:
  Material (float r, float g, float b);
public:
  static MaterialPtr Make (float r, float g, float b);
  virtual ~Material ();
  void SetAmbient (float r, float g, float b);
  void SetDiffuse (float r, float g, float b);
  void SetSpecular (float r, float g, float b);
  void SetShininess (float shi);
  virtual void Load ();
};

#endif