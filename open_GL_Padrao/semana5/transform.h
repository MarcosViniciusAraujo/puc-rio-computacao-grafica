#include <memory>
class Transform;
typedef std::shared_ptr<Transform> TransformPtr;

#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform {
  float m_mat[16];
protected:
  Transform ();
public:
  static TransformPtr Make ();
  virtual ~Transform ();
  void Translate (float x, float y, float z);
  void Scale (float x, float y, float z);
  void Rotate (float angle, float x, float y, float z);
  void GetMatrix (float mat[16]);
  void Load () const;
  void Unload () const;
};

#endif