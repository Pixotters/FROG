#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "Random.hpp"

#include <iostream> // delete

Level::Level()
  : Scene()
{ 
  m_player = new Player;
  m_gameObjects.push_back(m_player);
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
  delete m_player;
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


void Level::handleActions(Controller * c)
{
  /*
    for(auto it = c->getOneTime().begin(); it != c->getOneTime().end(); ++it)
    {
    if(it->second.compare("LEFT") ){
    movePlayer(-1);
    }
      
    if(it->second.compare("RIGHT") ){
    movePlayer(1);
    }
    }*/
  auto actions = c->getActions();
  while(not actions.empty() )
    {
      Action * a = actions.front();
      
      if(a->getName().compare("LEFT") == 0){
        movePlayer(-4);
      }
      
      if(a->getName().compare("RIGHT") == 0){
        movePlayer(4);
      }

      actions.pop();
    }
}


void Level::movePlayer(const short& x)
{
  std::cout<<"moving player H : "<< x << std::endl;
  m_player->getTransform().move(x, 0);
}
