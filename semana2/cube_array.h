#ifndef CUBE_ARRAY_H
#define CUBE_ARRAY_H

#include "shape.h"

class CubeArray : public Shape {
  float m_coords[24*3];
  float m_normals[24*3];
  unsigned int m_index[36];
protected:
public:
  CubeArray ();
  virtual ~CubeArray ();
  virtual void Draw ();
};
#endif