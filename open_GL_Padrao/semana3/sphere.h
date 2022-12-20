#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
  int m_nind;
  unsigned int* m_index;
  float* m_coords;
public:
  Sphere (int nstack=64, int nslice=64);
  virtual ~Sphere ();
  virtual void Draw ();
};
#endif