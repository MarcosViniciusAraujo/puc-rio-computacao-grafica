#include "sphere.h"
#include "grid.h"

#ifdef _WIN32
#include <windows.h>
#include <gl/gl.h>
#else
#include <OpenGL/gl.h>
#endif

#include <cmath>
#include <cstring>
#include <iostream>


#define PI 3.14159265f

Sphere::Sphere (int nstack, int nslice)
{
  Grid* grid = new Grid(nstack,nslice);
  m_nind = grid->IndexCount();
  m_index = new unsigned int[m_nind];
  m_coords = new float[3*grid->VertexCount()];
  // generate spherical coordinates
  int nc = 0;
  const float* verts = grid->GetCoords();
  for (int i=0; i<2*grid->VertexCount(); i+=2) {
    float theta = verts[i+0]*2*PI;
    float phi = verts[i+1]*PI;
    m_coords[nc+0] = sin(theta) * sin(PI-phi);
    m_coords[nc+1] = cos(PI-phi);
    m_coords[nc+2] = cos(theta) * sin(PI-phi);
    nc += 3;
  }
  // copy indices from grid
  memcpy(m_index,grid->GetIndices(),m_nind*sizeof(unsigned int));
}

Sphere::~Sphere () 
{
  delete [] m_coords;
  delete [] m_index;
}

void Sphere::Draw ()
{
  glVertexPointer(3, GL_FLOAT, 0, m_coords);
  glNormalPointer(GL_FLOAT, 0, m_coords);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glDrawElements(GL_TRIANGLES,m_nind,GL_UNSIGNED_INT,m_index);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}