#include <memory>
class Scene;
typedef std::shared_ptr<Scene> ScenePtr;

#ifndef SCENE_H
#define SCENE_H

#include "node.h"
#include "camera.h"
#include "light.h"
#include "engine.h"

#include <vector>

class Scene 
{
  NodePtr m_root;
  LightPtr m_light;
  LightPtr s_light;
  std::vector<EnginePtr> m_engines;
protected:
  Scene (NodePtr root, LightPtr light,LightPtr light2);
public:
  static ScenePtr Make (NodePtr root, LightPtr light=nullptr,LightPtr light2=nullptr);
  ~Scene ();
  void AddEngine (EnginePtr engine);
  void Update (float dt) const;
  void Render (CameraPtr camera) const;
};

#endif
