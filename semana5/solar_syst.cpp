#include "solar_syst.h"

const float DAY = 5.0f;     // amount of seconds to simulate a day
const float CYCLE = 20.0f;  // number of days in a moon cycle
const float YEAR = 60.0f;   // number of days in a year

SolarSyst::SolarSyst (TransformPtr eR, TransformPtr eT, TransformPtr mT)
: m_factor(1.0f), m_eR(eR), m_eT(eT), m_mT(mT)
{
}

SolarSystPtr SolarSyst::Make (TransformPtr eR, TransformPtr eT, TransformPtr mT)
{
  return SolarSystPtr(new SolarSyst(eR,eT,mT));
}

SolarSyst::~SolarSyst ()
{
}

void SolarSyst::SetSpeedFactor (float factor)
{
  m_factor = factor;
}

float SolarSyst::GetSpeedFactor () const
{
  return m_factor;
}

void SolarSyst::Update (float dt) 
{
  float ndays = dt / DAY * m_factor;
  m_eR->Rotate(360.0f*ndays,0.0f,1.0f,0.0f);
  m_eT->Rotate(360.0f*ndays/YEAR,0.0f,1.0f,0.0f);
  m_mT->Rotate(360.0f*ndays/CYCLE,0.0f,1.0f,0.0f);
}