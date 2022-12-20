#include <memory>
class Cube;
typedef std::shared_ptr<Cube> CubePtr;

#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

class Cube : public Shape {
protected:
  Cube ();
public:
  static CubePtr Make ();
  virtual ~Cube ();
  virtual void Draw ();
};
#endif