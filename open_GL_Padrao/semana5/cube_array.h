#include <memory>
class CubeArray;
typedef std::shared_ptr<CubeArray> CubeArrayPtr;

#ifndef CUBE_ARRAY_H
#define CUBE_ARRAY_H

#include "shape.h"

class CubeArray : public Shape {
  float m_coords[24*3];
  float m_normals[24*3];
  unsigned int m_index[36];
protected:
  CubeArray ();
public:
  static CubeArrayPtr Make ();
  virtual ~CubeArray ();
  virtual void Draw ();
};
#endif