#include "scene.h"
#include <iostream>
#include <GL/gl.h>


Scene::Scene (NodePtr root, LightPtr light,LightPtr light2)
: m_root(root), m_light(light),s_light(light2), m_engines()
{
}

ScenePtr Scene::Make (NodePtr root, LightPtr light, LightPtr light2)
{
  return ScenePtr(new Scene(root,light,light2));
}

Scene::~Scene ()
{
}

void Scene::AddEngine (EnginePtr engine)
{
  std::cout << engine;
  m_engines.push_back(engine);
}

void Scene::Update (float dt) const
{
  for (auto e : m_engines){
    
    e->Update(dt);
  }
}

void Scene::Render (CameraPtr camera) const
{
  camera->Setup();
  if (m_light != nullptr) {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    m_light->Setup();
  }
  if (s_light != nullptr) {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    s_light->Setup();


  }
  m_root->Render();
} 