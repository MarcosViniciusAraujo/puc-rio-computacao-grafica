#include "pyramid_array.h"

#include <GL/gl.h>

PyramidArray::PyramidArray ()
: m_coords{
    // back face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f,-0.5f,
    // front face: counter clockwise 
    -0.5f, 0.0f, 0.5f,
     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f, 0.5f,
    // left face: counter clockwise
    -0.5f, 0.0f,-0.5f,
     0.0f, 1.0f, 0.0f,
    -0.5f, 0.0f, 0.5f,
    // right face: counter clockwise
     0.5f, 0.0f,-0.5f,
     0.0f, 1.0f, 0.0f,
     0.5f, 0.0f, 0.5f,
    // bottom face: counter clockwise 
    -0.5f, 0.0f,-0.5f,
     0.5f, 0.0f,-0.5f,
     0.5f, 0.0f, 0.5f,
    -0.5f, 0.0f, 0.5f,

  },
  m_normals{
    // back face: counter clockwise 
     0.0f, 0.8320502943378437f,-0.5547001962252291f,
     0.0f, 0.8320502943378437f,-0.5547001962252291f,
     0.0f, 0.8320502943378437f,-0.5547001962252291f,
    // front face: counter clockwise 
     0.0f, 0.8320502943378437f, 0.5547001962252291f,
     0.0f, 0.8320502943378437f, 0.5547001962252291f,
     0.0f, 0.8320502943378437f, 0.5547001962252291f,
    // left face: counter clockwise
    -0.5547001962252291f, 0.8320502943378437f, 0.0f,
    -0.5547001962252291f, 0.8320502943378437f, 0.0f,
    -0.5547001962252291f, 0.8320502943378437f, 0.0f,
    // right face: counter clockwise
     0.5547001962252291f, 0.8320502943378437f, 0.0f,
     0.5547001962252291f, 0.8320502943378437f, 0.0f,
     0.5547001962252291f, 0.8320502943378437f, 0.0f,
    // bottom face: counter clockwise 
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,
     0.0f,-1.0f, 0.0f,

  },
  m_index{
    0,1,2,
    3,4,5,
    6,7,8,
    9,10,11,
    12,13,14,12,14,15
  }
{
}

PyramidArrayPtr PyramidArray::Make()
{
  return PyramidArrayPtr(new PyramidArray());
}

PyramidArray::~PyramidArray () 
{
}

void PyramidArray::Draw ()
{
  glVertexPointer(3, GL_FLOAT, 0, m_coords);
  glNormalPointer(GL_FLOAT, 0, m_normals);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_INT,m_index);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}