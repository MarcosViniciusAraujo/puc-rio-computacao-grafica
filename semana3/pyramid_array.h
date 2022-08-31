#ifndef PYRAMID_ARRAY_H
#define PYRAMID_ARRAY_H

#include "shape.h"

class PyramidArray : public Shape {
  float m_coords[16*3];
  float m_normals[16*3];
  unsigned int m_index[18];
protected:
public:
  PyramidArray ();
  virtual ~PyramidArray ();
  virtual void Draw ();
};
#endif