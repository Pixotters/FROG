#include "Scene.hpp"

#include "Player.hpp"


Scene::Scene()
  : State()
{
  m_entities.push_back(new Player);
}

Scene::~Scene()
{
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      delete(*it);
    }
  m_entities.clear();
}

void Scene::drawEntities(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
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
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      (*it)->update();
    }
}

