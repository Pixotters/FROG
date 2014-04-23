
#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "FROG/Control.hpp"
#include "FROG/Translator.hpp"

#include "FROG/App.hpp"

#include "FROG/Random.hpp"
#include "FROG/Rendering/Sprite.hpp"
#include "MovePlayer.hpp"
//#include "JoystickMove.hpp"

#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics.hpp>
#include <iostream> // TODO remove

using namespace frog;

class Collider : virtual public sap::ActionManager{

private:
  std::shared_ptr<Player> m_player;
  render::Renderer * m_renderer;
  std::list<std::shared_ptr<Target> > * m_targets;

public:
  Collider(std::shared_ptr<Player> p, std::list< std::shared_ptr<Target> > * t, render::Renderer * r) 
    : m_player(p), m_targets(t), m_renderer(r)
  {}

  virtual void onCollision(sap::Collisionable * a, sap::Collisionable * b){
       
    Player * p;
    Target * t1;
    Target * t2;
    if(
       ( (p = dynamic_cast<Player *>(a) )
         && (t2 = dynamic_cast<Target *>(b) ) )
       //      ||( (p = dynamic_cast<Player *>(b) )
       //          && (t2 = dynamic_cast<Target *>(a) ) )
       ){
      onCollision(p, t2);
    }
    if( (t1 = dynamic_cast<Target *>(a) )
        && (t2 = dynamic_cast<Target *>(b) ) ){
      onCollision(t1, t2);
    }
  }

  void onCollision(Player * a, Target * b){
    //    m_targets->remove(b);
    //    m_renderer->removeObject(b);
    
  }

  void onCollision(Target * a, Target * b){
    //    m_targets -> remove(b);
  }
  
  virtual void onSeparation(sap::Collisionable * a, sap::Collisionable * b){

  }

};


Level::Level(const AppInfo& appinfo)
  : Scene(appinfo.window), m_player(new Player), m_terrain(new GameObject)
{
  std::cerr << "Player is " << m_player << "/" << m_player.get() << std::endl;
  GameObject * g = dynamic_cast<GameObject *>(m_player.get());
  std::cerr << "Player converted is "<< g << std::endl;
  auto moveleft = new MovePlayer(m_player.get(), -128, 0, appinfo);
  auto moveright = new MovePlayer(m_player.get(), 128, 0, appinfo);
  auto moveup = new MovePlayer(m_player.get(), 0, -128, appinfo);
  auto movedown = new MovePlayer(m_player.get(), 0, 128, appinfo);

  auto qkey = new ctrl::KeyboardButton(sf::Keyboard::Q);
  auto dkey = new ctrl::KeyboardButton(sf::Keyboard::D);
  auto zkey = new ctrl::KeyboardButton(sf::Keyboard::Z);
  auto skey = new ctrl::KeyboardButton(sf::Keyboard::S);
  m_controller.bind(qkey, moveleft );    
  m_controller.bind(dkey, moveright );
  m_controller.bind(zkey, moveup );  
  m_controller.bind(skey,  movedown );
  m_controller.bind(new ctrl::JoystickButton(XBOX::X), moveleft );    

  m_controller.bind(new ctrl::JoystickButton(XBOX::B), moveright );

  m_controller.bind(new ctrl::JoystickButton(XBOX::Y), moveup );    

  m_controller.bind(new ctrl::JoystickButton(XBOX::A), movedown );

  //  m_controller.bind(new ctrl::MouseButton(sf::Mouse::Left),
  //                       new Bomb(m_ennemies) );

  //  m_controller.bind(new ctrl::MouseSimpleButton(sf::Mouse::Right),
  //                       new Bomb(m_ennemies) );
  //  m_controller.bind(new ctrl::JoystickSimpleButton(XBOX::HOME), 
  //                    new Bomb(m_ennemies) );
  Collider * am = new Collider(m_player, &m_targets, m_renderer);
  m_collider = new sap::LSAP(am);  
  addObject(m_player);
  //m_player->getComponent<Transform>()->setPosition( 400, 560 );
  m_player->transform.setPosition( 400, 560 );
  m_terrain->getComponent<Transform>()->setPosition(0, 0);
  addObject(m_terrain);
}

Level::~Level()
{
  //  delete m_player;
}

void Level::update(const AppInfo& appinfo)
{  
  Scene::update(appinfo);
  static Sprite * s = new Sprite(m_textureManager.get("FROG_TEXTURE") );
  static Sprite * s2 = new Sprite(m_textureManager.get("TERRAIN_TEXTURE") );
  std::cerr << "Sprite is "<< s <<std::endl;
  m_player->addComponent<Sprite>( s );
  m_terrain->addComponent<Sprite>( s2 );
  handleCommands( m_controller.update() );
  //  JoystickMove * jm = new JoystickMove(m_player, &m_controller);
  //  jm->execute();
  //  delete jm;  
  m_collider->updateObject( m_player.get() );
  updateEnemies();
  updateTargets();
  sf::Time t = m_clock.getElapsedTime();
  if( t.asSeconds() > 0.2f && m_targets.size() < 4 ){
    spawnTarget(appinfo);
  }
  if(t.asSeconds() > 0.4f ){
    spawnEnemy(appinfo);
    m_clock.restart();
  }
}

void Level::spawnEnemy(const AppInfo& appinfo)
{
  
  std::shared_ptr<Enemy> e(new Enemy(appinfo) );
  sf::RectangleShape * r = new sf::RectangleShape(sf::Vector2f(25,25) );
  r->setFillColor(sf::Color::Red);
  e->addComponent(new Sprite(m_textureManager.get("ENEMY_TEXTURE") ) );
  e->getComponent<Transform>()->setPosition(Random::get(100, 700), 50);
  m_ennemies.push_back(e );
  addObject(e);
}

void Level::spawnTarget(const AppInfo& appinfo)
{
  
  std::shared_ptr<Target> e(new Target(appinfo) );
  e->addComponent(new Sprite(m_textureManager.get("BONUS_TEXTURE") ) );
  e->getComponent<Transform>()->setPosition(Random::get(100, 700), Random::get(50, 550) );
  m_targets.push_back(e);
  addObject(e);
  
}

void Level::updateEnemies()
{
  
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      PhysicEngine::update( it->get() );
      if((*it)->getComponent<Transform>()->getPosition().x > 800 
         || (*it)->getComponent<Transform>()->getPosition().y > 600  ){
        removeObject(*it);    
        it->reset();
        *it = nullptr;
      }
    }
  m_ennemies.remove(nullptr);
}

void Level::updateTargets()
{
  for(auto it = m_targets.begin(); it != m_targets.end(); ++it)
    {      
      PhysicEngine::update( it->get() );
      m_collider->updateObject( it->get() );
      if((*it)->getComponent<Transform>()->getPosition().x > 800 
         || (*it)->getComponent<Transform>()->getPosition().y > 600 
         || (*it)->getComponent<Transform>()->getPosition().x < -32
         || (*it)->getComponent<Transform>()->getPosition().y < -32){
        removeObject(*it);
        it->reset();
        *it = nullptr;
      }  
      
    }
  m_targets.remove(nullptr);
}
