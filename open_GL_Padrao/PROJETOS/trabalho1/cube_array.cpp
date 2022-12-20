#include "cube_array.h"

#include <GL/gl.h>

CubeArray::CubeArray ()
: m_coords{
    // back face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
    -0.5f, 1.0f,-0.5f,
     0.5f, 1.0f,-0.5f,
     0.5f, 0.0f,-0.5f,
    // front face: counter clockwise 
    -0.5f, 0.0f, 0.5f,
     0.5f, 0.0f, 0.5f,
     0.5f, 1.0f, 0.5f,
    -0.5f, 1.0f, 0.5f,
    // left face: counter clockwise
    -0.5f, 0.0f,-0.5f,
    -0.5f, 0.0f, 0.5f,
    -0.5f, 1.0f, 0.5f,
    -0.5f, 1.0f,-0.5f,
    // right face: counter clockwise
     0.5f, 0.0f,-0.5f,
     0.5f, 1.0f,-0.5f,
     0.5f, 1.0f, 0.5f,
     0.5f, 0.0f, 0.5f,
    // botton face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
     0.5f, 0.0f,-0.5f,
     0.5f, 0.0f, 0.5f,
    -0.5f, 0.0f, 0.5f,
    // top face: counter clockwise
    -0.5f, 1.0f,-0.5f,
    -0.5f, 1.0f, 0.5f,
     0.5f, 1.0f, 0.5f,
     0.5f, 1.0f,-0.5f
  },
  m_normals{
    // back face: counter clockwise 
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
     0.0f, 0.0f,-1.0f,
    // front face: counter clockwise 
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 1.0f,
    // left face: counter clockwise
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    // right face: counter clockwise
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
    // botton face: counter clockwise 
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
    // top face: counter clockwise
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
  },
  m_index{
    0,1,2,0,2,3,
    4,5,6,4,6,7,
    8,9,10,8,10,11,
    12,13,14,12,14,15,
    16,17,18,16,18,19,
    20,21,22,20,22,23
  }
{
}

CubeArrayPtr CubeArray::Make ()
{
  return CubeArrayPtr(new CubeArray());
}

CubeArray::~CubeArray () 
{
}

void CubeArray::Draw ()
{
  glVertexPointer(3, GL_FLOAT, 0, m_coords);
  glNormalPointer(GL_FLOAT, 0, m_normals);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,m_index);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}