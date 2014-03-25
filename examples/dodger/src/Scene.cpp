#include "Scene.hpp"


namespace frog{

  Scene::Scene()
    : State()
  {
  }

  Scene::~Scene()
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        delete(*it);
      }
    m_gameObjects.clear();
  }

  void Scene::drawEntities(sf::RenderTarget& rt, sf::RenderStates rs) const
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        (*it)->draw(*m_renderer, rs);
      }
  }

  void Scene::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
  {
    drawEntities(rt, rs);
    State::draw(rt, rs);
  }

  void Scene::update()
  {
    for(auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
      {
        (*it)->update();
      }
  }


}
