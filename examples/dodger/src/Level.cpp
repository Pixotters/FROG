#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "Input/Button.hpp"
#include "Input/SimpleButton.hpp"
#include "Input/KeyboardButton.hpp"
#include "Input/MouseButton.hpp"
#include "Input/JoystickButton.hpp"
#include "Input/JoystickSimpleButton.hpp"
#include "Input/Xbox.hpp"

#include "App.hpp"

#include "Random.hpp"

#include "MovePlayer.hpp"
#include "Bomb.hpp"

Level::Level()
  : Scene()
{ 
  m_player = new Player;
  m_gameObjects.push_back(m_player);
  auto moveleft = new MovePlayer(m_player, -4, 0);
  auto moveright = new MovePlayer(m_player, 4, 0);
  auto moveup = new MovePlayer(m_player, 0, -8);
  auto movedown = new MovePlayer(m_player, 0, 8);
  App::instance()->getController()
    ->suscribe(new Input::KeyboardButton(sf::Keyboard::Q), moveleft );    
  App::instance()->getController()
    ->suscribe(new Input::KeyboardButton(sf::Keyboard::D), moveright );
  App::instance()->getController()
    ->suscribe(new Input::KeyboardSimpleButton(sf::Keyboard::Z), moveup );  
  App::instance()->getController()
    ->suscribe(new Input::KeyboardSimpleButton(sf::Keyboard::S),  movedown );
  App::instance()->getController()
    ->suscribe(new Input::JoystickButton(XBOX::X), moveleft );    
  App::instance()->getController()
    ->suscribe(new Input::JoystickButton(XBOX::B), moveright );
  App::instance()->getController()
    ->suscribe(new Input::JoystickButton(XBOX::Y), moveup );    
  App::instance()->getController()
    ->suscribe(new Input::JoystickButton(XBOX::A), movedown );
  App::instance()->getController()
    ->suscribe(new Input::MouseButton(sf::Mouse::Left),
               new Bomb(m_ennemies) );
  App::instance()->getController()
    ->suscribe(new Input::MouseSimpleButton(sf::Mouse::Right),
               new Bomb(m_ennemies) );
  App::instance()->getController()
    ->suscribe(new Input::JoystickSimpleButton(XBOX::HOME), 
               new Bomb(m_ennemies) );
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
  Enemy * e = new Enemy;
  e->getTransform().setPosition(Random::get(100, 700), 50);
  e->m_physics.addRotationForce(5.0f);
  e->m_physics.addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 7) ) );
  m_ennemies.push_back(e );
}

void Level::spawnTarget()
{
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


void Level::handleCommands(Controller * c)
{
  auto commands = c->getQueue();
  while(not commands.empty() )
    {
      Command * a = commands.front();
      a->execute();
      commands.pop();
    }
}


void Level::movePlayer(const short& x)
{
  m_player->getTransform().move(x, 0);
}
