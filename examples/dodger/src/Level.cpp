
#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "FROG/Control.hpp"
#include "FROG/Translator.hpp"

#include "FROG/App.hpp"

#include "FROG/Random.hpp"

#include "MovePlayer.hpp"
//#include "JoystickMove.hpp"
#include "Bomb.hpp"

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
  /*  m_textureManager.loadFromFile("assets/frog.png", PLAYER_TEXTURE);
      m_textureManager.loadFromFile("assets/donut.png", TARGET_TEXTURE);
      m_textureManager.loadFromFile("assets/troll.png", ENEMY_TEXTURE);*/
  auto moveleft = new MovePlayer(m_player.get(), -4, 0);
  auto moveright = new MovePlayer(m_player.get(), 4, 0);
  auto moveup = new MovePlayer(m_player.get(), 0, -8);
  auto movedown = new MovePlayer(m_player.get(), 0, 8);

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
  m_terrain->getTransform().setPosition(0, 0);
  addObject(m_terrain);
}

Level::~Level()
{
  //  delete m_player;
}

void Level::update(const AppInfo& appinfo)
{  
  Scene::update(appinfo);
  sf::Sprite * s = new sf::Sprite;
  s->setTexture(m_textureManager.get("FROG_TEXTURE") );
  m_player->addComponent(new render::RenderingComponent(s) );
  sf::Sprite * s2 = new sf::Sprite;
  s2->setTexture(m_textureManager.get("TERRAIN_TEXTURE") );
  m_terrain->addComponent(new render::RenderingComponent(s2) );
  handleCommands( m_controller.update() );
  //  JoystickMove * jm = new JoystickMove(m_player, &m_controller);
  //  jm->execute();
  //  delete jm;  
  m_collider->updateObject( m_player.get() );
  updateEnemies();
  updateTargets();
  sf::Time t = m_clock.getElapsedTime();
  if( t.asSeconds() > 0.2f && m_targets.size() < 4 ){
    spawnTarget();
  }
  if(t.asSeconds() > 0.4f ){
    spawnEnemy();
    m_clock.restart();
  }
}

void Level::spawnEnemy()
{
  std::shared_ptr<Enemy> e(new Enemy);
  /*
    sf::RectangleShape * r = new sf::RectangleShape(sf::Vector2f(25,25) );
    r->setFillColor(sf::Color::Red);
    e->addComponent(new render::RenderingComponent( r ) );
  */
  e->addComponent(new render::RenderingComponent(new sf::Sprite(m_textureManager.get("ENEMY_TEXTURE") ) ) );
  e->getTransform().setPosition(Random::get(100, 700), 50);
  m_ennemies.push_back(e );
  addObject(e);
}

void Level::spawnTarget()
{
  std::shared_ptr<Target> e(new Target);
  e->addComponent(new render::RenderingComponent(new sf::Sprite(m_textureManager.get("BONUS_TEXTURE") ) ) );
  e->getTransform().setPosition(Random::get(100, 700), Random::get(50, 550) );
  m_targets.push_back(e);
  addObject(e);
}

void Level::updateEnemies()
{
  
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      (*it)->update();
      PhysicEngine::update( it->get() );
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600  ){
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
      (*it)->update();      
      PhysicEngine::update( it->get() );
      m_collider->updateObject( it->get() );
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600 
         || (*it)->getTransform().getPosition().x < -32
         || (*it)->getTransform().getPosition().y < -32){
        removeObject(*it);
        it->reset();
        *it = nullptr;
      }  
      
    }
  m_targets.remove(nullptr);
}


void Level::movePlayer(const short& x)
{
  m_player->getTransform().move(x, 0);
}
