#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform {
  float m_mat[16];
public:
  Transform ();
  void Translate (float x, float y, float z);
  void Scale (float x, float y, float z);
  void Rotate (float angle, float x, float y, float z);
  void Load () const;
  void Unload () const;
};

#endif