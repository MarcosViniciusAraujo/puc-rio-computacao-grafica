#ifndef LIGHT_H
#define LIGHT_H

class Light {
  static int s_id;
  int m_id;
  float m_amb[4];
  float m_dif[4];
  float m_spe[4];
protected:
  Light ();
  int GetId ();
public:
  void SetColor (float r, float g, float b);
  virtual void Setup ();
};

#endif