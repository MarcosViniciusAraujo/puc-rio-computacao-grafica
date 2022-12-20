
#include <memory>
class Node;
typedef std::shared_ptr<Node> NodePtr;

#ifndef NODE_H
#define NODE_H

#include "appearance.h"
#include "node.h"
#include "shape.h"
#include "transform.h"
#include <vector>
#include <initializer_list>

class Node : public std::enable_shared_from_this<Node>
{
  std::weak_ptr<Node> m_parent;       // parent node 
  TransformPtr m_trf;                 // associated transformation
  std::vector<AppearancePtr> m_apps;  // associated appearances
  std::vector<ShapePtr> m_shps;       // associated shapes
  std::vector<NodePtr> m_nodes;       // child nodes

  void SetParent (NodePtr parent) {
    m_parent = parent;
  }
protected:
  Node (TransformPtr trf=nullptr, 
        std::initializer_list<AppearancePtr> apps={},
        std::initializer_list<ShapePtr> shps={}
       );
public:
  static NodePtr Make (TransformPtr trf=nullptr, 
                       std::initializer_list<AppearancePtr> apps={},
                       std::initializer_list<ShapePtr> shps={},
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (TransformPtr trf=nullptr, 
                       std::initializer_list<AppearancePtr> apps={},
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<NodePtr> nodes={});
  static NodePtr Make (std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<ShapePtr> shps={},
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<AppearancePtr> apps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (std::initializer_list<ShapePtr> shps,
                       std::initializer_list<NodePtr> nodes={}
                      );
  static NodePtr Make (TransformPtr trf,
                       std::initializer_list<NodePtr> nodes={}
                      );
  virtual ~Node ();
  void SetTransform (TransformPtr trf);
  void AddAppearance (AppearancePtr app);
  void AddShape (ShapePtr shp);
  void AddNode (NodePtr node);
  NodePtr GetParent () const;
  void GetMatrix (float mat[16]) const;
  void GetModelMatrix (float mat[16]);
  void Render () const;
};

#endif