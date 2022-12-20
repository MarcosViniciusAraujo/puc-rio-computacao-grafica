#include <memory>
class EnginePyr;
typedef std::shared_ptr<EnginePyr> EnginePyrPtr;

#ifndef ENGINE_PYR_H
#define ENGINE_PYR_H

#include "engine.h"
#include "transform.h"

class EnginePyr : public Engine
{
  float m_factor;     
  TransformPtr m_pR; 

protected:
  EnginePyr (TransformPtr pR);
public:
  static EnginePyrPtr Make (TransformPtr pR);
  ~EnginePyr ();
  void SetSpeedFactor (float factor);
  float GetSpeedFactor () const;
  void Update (float dt);
};

#endif