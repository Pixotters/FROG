#include "Level.hpp"

#include "Player.hpp"
#include "Element.hpp"

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
  if( t.asSeconds() > 0.7f ){
    spawn( );
    m_clock.restart();
  }
}

void Level::spawn()
{
  std::cout << "spawning"<<std::endl;
  Element * e = new Element;
  float t = m_clock.getElapsedTime().asSeconds();
  int x = (int) (t*10000);
  std::cout << "x = "<< x << " - t : "<<t<<std::endl;
  float px = 800 * (float(x%100))/100.0f;
  float vx = ((int)px)%2 == 0 ? -px/10 : px/10;
  e->getTransform().setPosition(px, -50);
  std::cout << "spawned at "<< px<< std::endl;
  e->m_physics.addVelocity(sf::Vector2f(vx, 10.0f) );
  m_ennemies.push_back(e );
  std::cout << "spawned"<<std::endl;
}

void Level::updateEnemies()
{
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      (*it)->update();
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600  ){
        //        delete (*it);
        //        m_ennemies.erase(it);
      }
    }
}
