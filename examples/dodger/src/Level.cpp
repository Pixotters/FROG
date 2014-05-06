#include "GUI.hpp"
#include "Level.hpp"

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


const unsigned short TERRAIN_LAYER = 0;
const unsigned short TARGET_LAYER = 1;
const unsigned short PLAYER_LAYER = 2;
const unsigned short ENEMY_LAYER = 3;
const unsigned short GUI_LAYER = 4;

Level::Level(AppInfo& appinfo)
  : Scene(), 
    m_appinfo(appinfo),
    m_player(new Player), 
    m_terrain(new GameObject), 
    m_gui(new GameObject),
    m_am(m_player, &m_targets, m_renderer)
{
  m_collider = new sap::LSAP(&m_am);  
  m_fontManager.loadFromFile("assets/fonts/Hyperspace_Bold.ttf", GUI_FONT);
}

Level::~Level()
{
    delete m_collider;
    m_ennemies.clear();
    m_targets.clear();
}

void Level::enter()
{
  setControls(m_player, m_appinfo );
  m_terrain->addComponent( new Sprite(m_textureManager.get("TERRAIN_TEXTURE") ), "RENDERING" );
  m_terrain->transform->setPosition(0, 0);
  m_terrain->transform->layer = TERRAIN_LAYER;
  addObject(m_terrain);
  m_player->addComponent( new Sprite(m_textureManager.get("FROG_TEXTURE") ), "RENDERING" );
  m_player->transform->setPosition( 400, 400 );
  m_player->transform->layer = PLAYER_LAYER;
  addObject(m_player);
  std::shared_ptr<GUI> pgui(new GUI(800, 64, 
                                    m_fontManager.get(GUI_FONT),
                                    3) );
  m_gui->addComponent( pgui, "GUI" );
  m_gui->transform->layer = GUI_LAYER;
  m_gui->addComponent( new RenderingComponent(pgui.get() ), "RENDERING" );
  addObject(m_gui);
}

void Level::update(const AppInfo& appinfo)
{  
  Scene::update(appinfo);
  //  m_collider->updateObject( m_player.get() );
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

void Level::setControls(std::shared_ptr<GameObject> go, const AppInfo& appinfo)
{
  std::shared_ptr<Command> moveleft(new MovePlayer(go.get(), -PLAYER_SPEED, 0, appinfo) );
  std::shared_ptr<Command> moveright(new MovePlayer(go.get(), PLAYER_SPEED, 0, appinfo) );
  std::shared_ptr<Command> moveup(new MovePlayer(go.get(), 0, -PLAYER_SPEED, appinfo) );
  std::shared_ptr<Command> movedown(new MovePlayer(go.get(), 0, PLAYER_SPEED, appinfo) );

  std::shared_ptr<Input> qkey(new KeyboardButton(sf::Keyboard::Q) );
  std::shared_ptr<Input> dkey(new KeyboardButton(sf::Keyboard::D) );
  std::shared_ptr<Input> zkey(new KeyboardButton(sf::Keyboard::Z) );
  std::shared_ptr<Input> skey(new KeyboardButton(sf::Keyboard::S) );
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

void Level::spawnEnemy()
{
  std::shared_ptr<GameObject> e(new GameObject() );
  e->transform->layer = ENEMY_LAYER;
  e->transform->setPosition(Random::get(100, 700), 50);
  sf::RectangleShape * r = new sf::RectangleShape(sf::Vector2f(25,25) );
  r->setFillColor(sf::Color::Red);
  //  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  //  m_boundingBox->setFillColor(sf::Color::Red);
  e->addComponent(new PhysicBody(), "PHYSICS");
  auto phi = e->getComponent<PhysicBody>("PHYSICS");
  phi->applyForce(sf::Vector2f(Random::get(-2,2), Random::get(4, 5.5) ) );
  e->addComponent(new RenderingComponent( r ), "RENDERING" );
  m_ennemies.push_back(e);
  addObject(e);
}

void Level::spawnTarget()
{
  
  std::shared_ptr<GameObject> e(new GameObject() );
  //    m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  //  m_boundingBox->setFillColor(sf::Color::Green);
  e->addComponent(new Sprite(m_textureManager.get("BONUS_TEXTURE") ), "RENDERING" );
  e->transform->setPosition(Random::get(100, 700), Random::get(50, 550) );
  e->transform->layer = TARGET_LAYER;
  e->transform->setScale(0.5f, 0.5f);
  e->addComponent(new PhysicBody(), "PHYSICS");
  auto phi = e->getComponent<PhysicBody>("PHYSICS");
  phi->applyForce(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                               Random::get(-10, 10) / 10.f ) ); 
  m_targets.push_back(e);
  addObject(e);
  
}

void Level::updateEnemies()
{
  for(auto it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
    {      
      //      PhysicEngine::update( it->get() );
      if((*it)->getComponent<Transform>("TRANSFORM")->getPosition().x > 800 
         || (*it)->getComponent<Transform>("TRANSFORM")->getPosition().y > 600)
        {
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
      //      PhysicEngine::update( it->get() );
      //      m_collider->updateObject( it->get() );
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
