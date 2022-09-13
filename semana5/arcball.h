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
  Arcball (float distance);
public:
  static ArcballPtr Make (float distance);
  void InitMouseMotion (int x, int y);
  void AccumulateMouseMotion (int x, int y);
  const float* GetMatrix () const;
};

#endif

