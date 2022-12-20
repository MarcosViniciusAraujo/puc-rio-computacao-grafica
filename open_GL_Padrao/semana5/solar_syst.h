#include <memory>
class SolarSyst;
typedef std::shared_ptr<SolarSyst> SolarSystPtr;

#ifndef SOLAR_SYST_H
#define SOLAR_SYST_H

#include "engine.h"
#include "transform.h"

class SolarSyst : public Engine
{
  float m_factor;     // speed factor
  TransformPtr m_eR;  // earth rotation
  TransformPtr m_eT;  // earth translation
  TransformPtr m_mT;  // moon translation
protected:
  SolarSyst (TransformPtr eR, TransformPtr eT, TransformPtr mT);
public:
  static SolarSystPtr Make (TransformPtr eR, TransformPtr eT, TransformPtr mT);
  ~SolarSyst ();
  void SetSpeedFactor (float factor);
  float GetSpeedFactor () const;
  void Update (float dt);
};

#endif