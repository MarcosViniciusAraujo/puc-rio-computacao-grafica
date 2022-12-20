#include <memory>

class Spotlight;
typedef std::shared_ptr<Spotlight> SpotlightPtr;

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <GL/gl.h>
#include "objlight.h"

class Spotlight : public ObjLight {
  float m_pos[4];
  GLfloat m_direct[3];
  GLfloat angulo;
  GLfloat concentracao;
protected:
  Spotlight (float x, float y, float z, float w, GLfloat xD, GLfloat yD, GLfloat zD, GLfloat angle, GLfloat concentracao);
public:
  static SpotlightPtr Make (float x, float y, float z, float w, GLfloat xD, GLfloat yD, GLfloat zD, GLfloat angle, GLfloat concentracao);
  ~Spotlight ();
  void SetPosition (float x, float y, float z, float w=1.0f);
  void SetDirect(GLfloat xD, GLfloat yD, GLfloat zD);
  virtual int Setup () const;
};

#endif