#include <memory>
class Light;
typedef std::shared_ptr<Light> LightPtr;

#ifndef LIGHT_H
#define LIGHT_H

#include "node.h"

class Light {
  static int s_id;
  int m_id;
  float m_amb[4];
  float m_dif[4];
  float m_spe[4];
  NodePtr m_reference;
protected:
  Light ();
  int GetId () const;
public:
  virtual ~Light ();
  void SetAmbient (float r, float g, float b);
  void SetDiffuse (float r, float g, float b);
  void SetSpecular (float r, float g, float b);
  void SetReference (NodePtr reference);
  NodePtr GetReference () const;

  virtual int Setup () const;
};

#endif