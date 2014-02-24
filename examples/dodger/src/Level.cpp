#include "Level.hpp"

#include "Player.hpp"
#include "Element.hpp"

#include "Random.hpp"

#include <iostream> // delete

Level::Level()
  : Scene()
{ 
  m_gameObjects.push_back(new Player);
  /*  Element * e = new Element;
      e->getTransform().setPosition(100, 100);
      e->m_physics.addVelocity(sf::Vector2f(2, 1) );
      e->m_physics.addAcceleration(sf::Vector2f(-0.001f, -.01f) );
      m_gameObjects.push_back(e);
  */
 
}

Level::~Level()
{

}

void Level::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  Scene::draw(rt, rs);
    //  Scene::drawEntities(rt, rs);
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      (*it)->draw(rt, rs);
    }  
}

void Level::update()
{  
  Scene::update();
  updateEnemies();
  sf::Time t = m_clock.getElapsedTime();
  if( t.asSeconds() > 0.4f ){
    spawn( );
    m_clock.restart();
  }
}

void Level::spawn()
{
  std::cout << "spawning "<< m_ennemies.size() <<std::endl;
  Element * e = new Element;
  e->getTransform().setPosition(Random::get(100, 700), -50);
  e->m_physics.addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 7) ) );
  m_ennemies.push_back(e );
}

void Level::updateEnemies()
{
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      (*it)->update();
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600  ){
        delete (*it);
        *it = nullptr;
      }
    }
  m_ennemies.remove(nullptr);
}
