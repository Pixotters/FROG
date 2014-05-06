
#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "FROG/Control.hpp"
#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Debug.hpp"
#include "FROG/Translator.hpp"

#include "FROG/App.hpp"

#include "FROG/Random.hpp"
#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Rendering/TextSprite.hpp"
#include "FROG/Physics/PhysicBody.hpp"
#include "MovePlayer.hpp"
#include "JoystickMover.hpp"

#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics.hpp>
#include <iostream> // TODO remove

using namespace frog;

#define PLAYER_SPEED 512

class Collider : virtual public sap::ActionManager{

private:
  std::shared_ptr<Player> m_player;
  Renderer * m_renderer;
  std::list<std::shared_ptr<Target> > * m_targets;

public:
  Collider(std::shared_ptr<Player> p, std::list< std::shared_ptr<Target> > * t, Renderer * r) 
    : m_player(p), m_renderer(r), m_targets(t)
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

  void onCollision(Player *, Target *){
    //    m_targets->remove(b);
    //    m_renderer->removeObject(b);
    
  }

  void onCollision(Target *, Target *){
    //    m_targets -> remove(b);
  }
  
  virtual void onSeparation(sap::Collisionable *, sap::Collisionable *){

  }

};


Level::Level()
  : Scene(), 
    m_player(new Player), 
    m_terrain(new GameObject), 
    m_gui(new GameObject)
{
  Collider * am = new Collider(m_player, &m_targets, m_renderer);
  m_collider = new sap::LSAP(am);  
  m_player->transform->setPosition( 400, 60 );
  m_terrain->getComponent<Transform>("TRANSFORM")->setPosition(0, 0);
  m_gui->transform->layer = 4;
  m_player->transform->layer = 2;
  m_terrain->transform->layer = 0;
  m_fontManager.loadFromFile("assets/fonts/Hyperspace_Bold.ttf", GUI_FONT);
}

Level::~Level()
{
  //  delete m_player;
}

void Level::update(const AppInfo& appinfo)
{  
  Scene::update(appinfo);
  static bool added = false;
  if ( not added )
    {
      setControls(m_player.get(), appinfo );
      m_terrain->addComponent( new Sprite(m_textureManager.get("TERRAIN_TEXTURE") ), "RENDERING" );
      m_player->addComponent( new Sprite(m_textureManager.get("FROG_TEXTURE") ), "RENDERING" );
      m_gui->addComponent( new TextSprite("score", m_fontManager.get(GUI_FONT) ), "RENDERING" );
      m_gui->transform->setPosition( 400, 10);
      m_gui->getComponent<TextSprite>("RENDERING")->setColor(sf::Color::Red);
      addObject(m_terrain);
      addObject(m_player);
      addObject(m_gui);
      added = true;
    }
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

void Level::setControls(GameObject * go, const AppInfo& appinfo)
{
  auto moveleft = new MovePlayer(m_player.get(), -PLAYER_SPEED, 0, appinfo);
  auto moveright = new MovePlayer(m_player.get(), PLAYER_SPEED, 0, appinfo);
  auto moveup = new MovePlayer(m_player.get(), 0, -PLAYER_SPEED, appinfo);
  auto movedown = new MovePlayer(m_player.get(), 0, PLAYER_SPEED, appinfo);

  auto qkey = new KeyboardButton(sf::Keyboard::Q);
  auto dkey = new KeyboardButton(sf::Keyboard::D);
  auto zkey = new KeyboardButton(sf::Keyboard::Z);
  auto skey = new KeyboardButton(sf::Keyboard::S);
  std::shared_ptr<ControlComponent> ctrl(new ControlComponent(appinfo.eventList));
  ctrl->bind(qkey, moveleft );    
  ctrl->bind(dkey, moveright );
  ctrl->bind(zkey, moveup );  
  ctrl->bind(skey,  movedown );
  go->addComponent(ctrl, "CONTROL");
  go->addComponent( new JoystickMover(PLAYER_SPEED/60.0f, 
                                                     (sf::Joystick::Axis)XBOX::LSTICK_X, 
                                                     (sf::Joystick::Axis)XBOX::LSTICK_Y, 
                                      25),
                    "JOYSTICK"); 
}

void Level::spawnEnemy(const AppInfo& appinfo)
{
  std::shared_ptr<GameObject> e(new GameObject() );
  sf::RectangleShape * r = new sf::RectangleShape(sf::Vector2f(25,25) );
  r->setFillColor(sf::Color::Red);
  //  e->addComponent(new Sprite(m_textureManager.get("ENEMY_TEXTURE") ), "RENDERING" );
  e->addComponent(new PhysicBody(), "PHYSICS");
  auto phi = e->getComponent<PhysicBody>("PHYSICS");
  phi->applyForce(sf::Vector2f(Random::get(-2,2), Random::get(4, 5.5) ) );
  e->addComponent(new RenderingComponent(r), "RENDERING" );
  e->getComponent<Transform>("TRANSFORM")->setPosition(Random::get(100, 700), 50);
  e->transform->layer = 3;
  m_ennemies.push_back(e);
  addObject(e);
}

void Level::spawnTarget(const AppInfo& appinfo)
{
  
  std::shared_ptr<Target> e(new Target(appinfo) );
  e->addComponent(new Sprite(m_textureManager.get("BONUS_TEXTURE") ), "RENDERING" );
  e->getComponent<Transform>("TRANSFORM")->setPosition(Random::get(100, 700), Random::get(50, 550) );
  e->transform->layer = 1;
  m_targets.push_back(e);
  addObject(e);
  
}

void Level::updateEnemies()
{
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      PhysicEngine::update( it->get() );
      if((*it)->getComponent<Transform>("TRANSFORM")->getPosition().x > 800 
         || (*it)->getComponent<Transform>("TRANSFORM")->getPosition().y > 600  ){
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
      auto tr = (*it)->getComponent<Transform>("TRANSFORM");
      if ( tr->getPosition().x > 800 
         || tr->getPosition().y > 600 
         || tr->getPosition().x < -32
         || tr->getPosition().y < -32){
        removeObject(*it);
        it->reset();
        *it = nullptr;
      }  
      
    }
  m_targets.remove(nullptr);
}
