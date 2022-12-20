#include "node.h"
#include "error.h"
#include <GL/gl.h>

#include <iostream>

Node::Node (TransformPtr trf, 
            std::initializer_list<AppearancePtr> apps,
            std::initializer_list<ShapePtr> shps
           )
: m_parent(),
  m_trf(trf),
  m_apps(apps),
  m_shps(shps),
  m_nodes()
{
}

NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(trf,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (TransformPtr trf, 
                    std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(trf,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<NodePtr> nodes)
{
  NodePtr ptr(new Node(nullptr,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,apps,shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<AppearancePtr> apps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,apps,{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (TransformPtr trf,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(trf,{},{}));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}
NodePtr Node::Make (std::initializer_list<ShapePtr> shps,
                    std::initializer_list<NodePtr> nodes
                   )
{
  NodePtr ptr(new Node(nullptr,{},shps));
  for (auto node : nodes)
    ptr->AddNode(node);
  return ptr;
}

Node::~Node () 
{
}

void Node::SetTransform (TransformPtr trf)
{
  m_trf = trf;
}
void Node::AddAppearance (AppearancePtr app)
{
  m_apps.push_back(app);
}
void Node::AddShape (ShapePtr shp)
{
  m_shps.push_back(shp);
}
void Node::AddNode (NodePtr node)
{
  m_nodes.push_back(node);
  node->SetParent(shared_from_this());
}
NodePtr Node::GetParent () const
{
  return m_parent.lock();
}
void Node::GetMatrix (float mat[16]) const
{
  if (m_trf) {
    m_trf->GetMatrix(mat);
  }
  else {
    for (int i=0; i<16; ++i)
      mat[i] = i % 5 == 0 ? 1.0f : 0.0f;
  }
}
void Node::GetModelMatrix (float mat[16]) 
{
  GetMatrix(mat);
  NodePtr node = GetParent();
  while (node != nullptr) {
    float m[16];
    node->GetMatrix(m);
    glPushMatrix();
    glLoadMatrixf(m);
    glMultMatrixf(mat);
    glGetFloatv(GL_MODELVIEW_MATRIX,mat);
    glPopMatrix();
    node = node->GetParent();
  } 
}

void Node::Render () const
{
  // load
  if (m_trf) 
    m_trf->Load();
  for (AppearancePtr app : m_apps)
    app->Load();
  // draw
  for (ShapePtr shp : m_shps)
    shp->Draw();
  for (NodePtr node : m_nodes)
    node->Render();
  // unload
  for (AppearancePtr app : m_apps)
    app->Unload();
  if (m_trf)
    m_trf->Unload();
  Error::Check("end node render");
}
