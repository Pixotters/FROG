#include "Level.hpp"

#include "Player.hpp"
#include "Element.hpp"

#include <iostream> // delete

Level::Level()
  : Scene()
{ 
  m_gameObjects.push_back(new Player);
  Element * e = new Element;
  std::cout << "e at "<<e->getTransform().getPosition().x<<std::endl;
  e->getTransform().setPosition(300, 100);
  e->m_physics.addVelocity(sf::Vector2f(2, 4) );
  std::cout << "e at "<<e->getTransform().getPosition().x<<std::endl;
  m_gameObjects.push_back(e);
 
 
}

Level::~Level()
{

}


void Level::update()
{
  sf::Time t = m_clock.getTimeElapsed();
  if( t.asSeconds() > 1.5f ){
    m_clock.restart();
    spawn();
  }
}
