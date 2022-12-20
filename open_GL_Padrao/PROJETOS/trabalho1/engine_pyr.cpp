#include "engine_pyr.h"
#include <iostream>
const float CYCLE = 20.0f;  // number of days in a moon cycle


EnginePyr::EnginePyr (TransformPtr pR)
: m_factor(1.0f), m_pR(pR)
{
}

EnginePyrPtr EnginePyr::Make (TransformPtr pR)
{
  return EnginePyrPtr(new EnginePyr(pR));
}

EnginePyr::~EnginePyr ()
{
}

void EnginePyr::SetSpeedFactor (float factor)
{
  m_factor = factor;
}

float EnginePyr::GetSpeedFactor () const
{
  return m_factor;
}

void EnginePyr::Update (float dt) 
{
  float ndays = dt / 5.0f * m_factor;
  m_pR->Rotate(360.0f*ndays,0.0f,1.0f,0.0f);
}