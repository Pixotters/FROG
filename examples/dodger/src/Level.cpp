#include "Level.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Target.hpp"

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
  spawnEnemy();
}

Level::~Level()
{

}

void Level::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  Scene::draw(rt, rs);
  for(auto it = m_targets.begin(); it != m_targets.end(); ++it)
    {      
      (*it)->draw(rt, rs);
    }
  Scene::drawEntities(rt, rs);
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      (*it)->draw(rt, rs);
    }   
}

void Level::update()
{  
  Scene::update();
  updateEnemies();
  updateTargets();
  sf::Time t = m_clock.getElapsedTime();
  if( t.asSeconds() > 0.2f && m_targets.size() < 5 ){
    spawnTarget();
  }
  if(t.asSeconds() > 0.4f ){
    spawnEnemy();
    m_clock.restart();
  }
}

void Level::spawnEnemy()
{
  std::cout << "spawning enemy"<< m_ennemies.size() <<std::endl;
  Enemy * e = new Enemy;
  e->getTransform().setPosition(Random::get(100, 700), 50);
  e->m_physics.addRotationForce(5.0f);
  e->m_physics.addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 7) ) );
  m_ennemies.push_back(e );
}

void Level::spawnTarget()
{
  std::cout << "spawning target"<< m_targets.size() <<std::endl;
  Target * e = new Target;
  e->getTransform().setPosition(Random::get(100, 700), Random::get(50, 550) );
  e->m_physics.addVelocity(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                                        Random::get(-10, 10) / 10.f ) ); 
  e->m_physics.addAcceleration(  e->m_physics.getVelocity() / -100.0f );
  e->m_physics.addGrowth(sf::Vector2f(-0.005f, -0.005f) );
  std::cout<< "target's velocity : "\
           << e->m_physics.getVelocity().x <<","\
           << e->m_physics.getVelocity().y <<std::endl;
  m_targets.push_back(e);
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

void Level::updateTargets()
{
  for(auto it = m_targets.begin(); it != m_targets.end(); ++it)
    {      
      (*it)->update();
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600 
         || (*it)->getTransform().getPosition().x < -32
         || (*it)->getTransform().getPosition().y < -32){
        delete (*it);
        *it = nullptr;
      }
    }
  m_targets.remove(nullptr);
}
