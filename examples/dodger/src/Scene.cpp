#include "Scene.hpp"

#include "Player.hpp"

#include <iostream> // delete


Scene::Scene()
  : State()
{
  m_renderer = new Renderer(800, 600);
  m_entities.push_back(new Player);
}

Scene::~Scene()
{

}

void Scene::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  m_renderer->clear(sf::Color::Black);
  std::cerr << "Scene draws entities in renderer" << m_renderer->getSize().x << std::endl;
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      //      m_renderer->draw( *it, rs);
      (*it)->draw(*m_renderer, rs);
    }
  std::cerr << "Scene tells renderer to draw in the window "<< rt.getSize().x << std::endl;
  //  m_renderer->display();
  m_renderer->display();
  m_renderer->draw(rt, rs);
}

void Scene::update(const sf::Time& dt)
{
  for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
      (*it)->update(dt);
    }
}

