#include "scene.h"

#include <GL/gl.h>


Scene::Scene (NodePtr root, LightPtr light)
: m_root(root), m_light(light), m_engines()
{
}

ScenePtr Scene::Make (NodePtr root, LightPtr light)
{
  return ScenePtr(new Scene(root,light));
}

Scene::~Scene ()
{
}

void Scene::AddEngine (EnginePtr engine)
{
  m_engines.push_back(engine);
}

void Scene::Update (float dt) const
{
  for (auto e : m_engines)
    e->Update(dt);
}

void Scene::Render (CameraPtr camera) const
{
  camera->Setup();
  if (m_light != nullptr) {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    m_light->Setup();
  }
  m_root->Render();
}