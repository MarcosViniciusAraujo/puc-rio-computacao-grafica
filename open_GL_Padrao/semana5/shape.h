#include <memory>
class Shape;
typedef std::shared_ptr<Shape> ShapePtr;

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
  virtual ~Shape () {}
  virtual void Draw () = 0;
};

#endif