#include <memory>
class Arcball;
typedef std::shared_ptr<Arcball> ArcballPtr;

#ifndef ARCBALL_H
#define ARCBALL_H

class Arcball {
  float m_distance;
  float m_x0, m_y0;
  float m_mat[16];
protected:
public:
  Arcball (float distance);
  void InitMouseMotion (float x, float y);
  void AccumulateMouseMotion (float x, float y);
  const float* GetMatrix () const;
};

#endif

