#include <memory>
class TampaArray;
typedef std::shared_ptr<TampaArray> TampaArrayPtr;

#ifndef TAMPA_ARRAY_H
#define TAMPA_ARRAY_H

#include "shape.h"

class TampaArray : public Shape {
  float m_coords[(5*4 + (7*7))*3]; // outras 5 faces, 4 pontos, 3 coordenadas  
                                   //+ n de pontos da tampa ao quadrado * 3 coordenadas 
  float m_normals[(5*4 + (7*7))*3];     // outras 5 faces, 4 pontos, 3 coordenadas  
                                        //+ n de pontos da base da tampa ao quadrado * 3 coordenadas 
  unsigned int m_index[(5 + (7-1)*(7-1))*6 ]; // 5 faces * 6 pontos + 
                                              //(n de pontos da base da tampa - 1) ao quadrado * 6
protected:
  TampaArray ();
public:
  static TampaArrayPtr Make ();
  virtual ~TampaArray ();
  virtual void Draw ();
};
#endif