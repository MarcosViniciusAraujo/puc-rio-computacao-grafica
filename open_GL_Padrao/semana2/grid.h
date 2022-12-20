#ifndef GRID_H
#define GRID_H

class Grid {
  int m_nx, m_ny;
  float* m_coords;
  unsigned int* m_indices;
protected:
public:
  Grid (int nx, int ny);
  virtual ~Grid ();
  int GetNx ();
  int GetNy ();
  int VertexCount ();
  int IndexCount ();
  const float* GetCoords () const;
  const unsigned int* GetIndices () const;
};
#endif