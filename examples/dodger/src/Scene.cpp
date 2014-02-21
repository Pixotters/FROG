#include "Scene.hpp"

#include "Player.hpp"

Scene::Scene()
  : State()
{
  m_entities.push_back(new Player);
}

Scene::~Scene()
{

}

void Scene::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      (*it)->draw(rt, rs);
    }
}

void Scene::update(const sf::Time& dt)
{
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      (*it)->update(dt);
    }
}

