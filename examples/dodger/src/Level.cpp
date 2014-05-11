#include "GUI.hpp"
#include "Level.hpp"
#include "End.hpp"
#include "MovePlayer.hpp"

#include "FROG/Control.hpp"
#include "FROG/Control/JoystickMover.hpp"
#include "FROG/Random.hpp"
#include "FROG/Collision/BoxCollider.hpp"
#include "FROG/Collision/LSAP.hpp"
#include "FROG/Component/AudioSource.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Rendering/TextSprite.hpp"
#include "FROG/Physics/PhysicBody.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <exception>

using namespace frog;

#define PLAYER_SPEED 512


const unsigned short TERRAIN_LAYER = 0;
const unsigned short TARGET_LAYER = 1;
const unsigned short PLAYER_LAYER = 2;
const unsigned short ENEMY_LAYER = 3;
const unsigned short GUI_LAYER = 4;

Level::Level(AppInfo& appinfo)
  : Scene(appinfo), 
    m_player(new Player), 
    m_terrain(new GameObject), 
    m_gui(new GameObject)
{
  m_collisionManager = new LSAP();  
  m_fontManager.loadFromFile("assets/fonts/Hyperspace_Bold.ttf", GUI_FONT);
  if( not loadFromFile("assets/scenes/level.xml") )
    throw std::runtime_error("Cannot load Level");
      
}

Level::~Level()
{
  delete m_collisionManager;
  m_enemies.clear();
  m_targets.clear();
}

void Level::enter()
{
  //  if (m_music.openFromFile("assets/musics/Canal_Street_Blues.ogg") )
  //    m_music.play();
  //  sf::SoundBuffer& music = defaultSoundManager.get("MUSIC");
  //  m_player->addComponent(new AudioSource(), "MUSIC");
  //  m_player->getComponent<AudioSource>("MUSIC")->playSound(music);
  setControls(m_player, appInfo );
  m_terrain->addComponent( new Sprite(defaultTextureManager.get("TERRAIN_TEXTURE") ), "RENDERING" );
  m_terrain->transform->setPosition(0, 0);
  m_terrain->transform->layer = TERRAIN_LAYER;
  addObject(m_terrain);
  m_player->transform->layer = PLAYER_LAYER;
  m_player->addComponent( new Sprite(defaultTextureManager.get("FROG_TEXTURE") ),
                          "RENDERING" );
  auto col_script = [this](Collision c){
    try{
      auto type = c.second->getProperty<TYPE_ID>("type");
      if (type == ENEMY_TYPE)
        {          
          if (not this->m_player->invincible)
            {
              this->m_player->hit();
              this->m_player->getComponent<AudioSource>("AUDIO")
                ->playSound(this->defaultSoundManager.get("PUNCH") );
              updateLives();
            }
        }
      else if (type == TARGET_TYPE)
        {
          auto player = this->m_player;
          if (Random::get(0, 1) == 0)
            player->getComponent<AudioSource>("AUDIO")->playSound(this->defaultSoundManager.get("BITE_1") );
          else
            player->getComponent<AudioSource>("AUDIO")->playSound(this->defaultSoundManager.get("BITE_2") );
          //          this->removeTarget(c.second);
          player->row += 1;
          if (player->row >= 10)
            {
              player->multiplier++;
              player->row = 0;
            }
          player->score += (2*player->multiplier)+5;
          updateScore();
          updateRow();

        }
    }catch(std::logic_error e)
      {

      }
  };
  m_player->getComponent<BoxCollider>("COLLIDER")->setScript(col_script);
  addObject(m_player);
  m_collisionManager->addObject(m_player);
  std::shared_ptr<GUI> pgui(new GUI(800, 64, 
                                    m_fontManager.get(GUI_FONT),
                                    3) );
  m_gui->addComponent( pgui, "GUI" );
  m_gui->transform->layer = GUI_LAYER;
  m_gui->addComponent( new RenderingComponent(pgui.get() ), "RENDERING" );
  addObject(m_gui);
}

void Level::postupdate()
{  
  m_collisionManager->update();
  updatePlayer();
  updateEnemies();
  updateTargets();
  sf::Time t = appInfo.clock.getElapsedTime();
  if( t.asSeconds() > 0.2f && m_targets.size() < 4 ){
    spawnTarget();
  }
  if(t.asSeconds() > 0.4f ){
    spawnEnemy();
    appInfo.clock.restart();
  }
}

void Level::setControls(std::shared_ptr<GameObject> go, const AppInfo& appinfo)
{
  std::shared_ptr<Command> moveleft(new MovePlayer(go.get(), -PLAYER_SPEED, 0, appinfo) );
  std::shared_ptr<Command> moveright(new MovePlayer(go.get(), PLAYER_SPEED, 0, appinfo) );
  std::shared_ptr<Command> moveup(new MovePlayer(go.get(), 0, -PLAYER_SPEED, appinfo) );
  std::shared_ptr<Command> movedown(new MovePlayer(go.get(), 0, PLAYER_SPEED, appinfo) );

  auto qkey = KeyboardButton::create(sf::Keyboard::Q);
  auto dkey = KeyboardButton::create(sf::Keyboard::D);
  auto zkey = KeyboardButton::create(sf::Keyboard::Z);
  auto skey = KeyboardButton::create(sf::Keyboard::S);
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
  std::shared_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(25,25) ) );
  r->setFillColor(sf::Color::Red);
  r->setOutlineThickness(2);
  r->setOutlineColor(sf::Color::Black);
  e->addComponent(new RenderingComponent( r ), "RENDERING" );
  e->addComponent(new PhysicBody(), "PHYSICS");
  e->transform->layer = ENEMY_LAYER;
  e->transform->setPosition(Random::get(100, 700), 50);
  e->transform->setOrigin(12, 12);
  auto phi = e->getComponent<PhysicBody>("PHYSICS");
  phi->addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 5.5) ) );
  phi->addRotation( Random::get(-20, 20) );
  auto x_center = r->getLocalBounds().left + (r->getLocalBounds().width/2.0);
  auto y_center = r->getLocalBounds().top + (r->getLocalBounds().height/2.0);
  e->transform->setOrigin( sf::Vector2f(x_center, y_center) );
  e->addComponent(new BoxCollider(sf::Vector2u(25,25) ), "COLLIDER");
  e->addProperty("type", ENEMY_TYPE);
  m_collisionManager->addObject(e);
  m_enemies.push_back(e);
  addObject(e);

}

void Level::spawnTarget()
{
  std::shared_ptr<GameObject> e(new GameObject() );
  e->addComponent(new Sprite(defaultTextureManager.get("BONUS_TEXTURE") ), "RENDERING" );
  e->transform->setPosition(Random::get(100, 700), Random::get(50, 550) );
  e->transform->layer = TARGET_LAYER;
  e->transform->setOrigin(32, 32);
  e->addComponent(new PhysicBody(), "PHYSICS");
  auto phi = e->getComponent<PhysicBody>("PHYSICS");
  phi->addVelocity(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                                Random::get(-10, 10) / 10.f ) );  
  phi->addGrowth( sf::Vector2f(-0.005f, -0.005f) );
  phi->addRotation( Random::get(-20, 20) );  
  e->addComponent(new BoxCollider(sf::Vector2u(64,64) ), "COLLIDER");
  e->addProperty("type", TARGET_TYPE);
  m_targets.push_back(e);
  //  m_collisionManager->addObject(e);
  addObject(e);  
}

void Level::updatePlayer()
{
  // replacing player when out of screen
  auto pos = m_player->transform->getPosition();
  float x_dec = 0, y_dec = 0;
  if (pos.x < 0)
    x_dec = -pos.x;
  if (pos.y < 64)
    y_dec = 64-pos.y;
  if (pos.x > appInfo.window.getSize().x)
    x_dec = appInfo.window.getSize().x - pos.x;
  if (pos.y > appInfo.window.getSize().y)
    y_dec = appInfo.window.getSize().y - pos.y;
  m_player->transform->move(x_dec, y_dec);

  // checking game over
  if (m_player->lives <= 0)
    {
      appInfo.stateManager.change(new End(appInfo, m_player->score) );
    }
  // checking if vulnerable
  if (m_player->invincible)
    {
      m_player->timer += appInfo.deltaTime;
      m_player->checkTime();
    }
}

void Level::updateEnemies()
{
  for(auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
    {      
      if((*it)->transform->getPosition().x > 800 
         || (*it)->transform->getPosition().y > 600)
        {
          removeObject(*it);
          m_collisionManager->removeObject(*it);
          it->reset();
          *it = nullptr;
        }
    }
  m_enemies.remove(nullptr);
}

void Level::updateTargets()
{
  for(auto it = m_targets.begin(); it != m_targets.end(); ++it)
    {      
      auto tr = (*it)->transform;
      if ( tr->getPosition().x > 800 
           || tr->getPosition().y > 600 
           || tr->getPosition().x < -32
           || tr->getPosition().y < -32
           || tr->getScale().x < 0.1
           || tr->getScale().y < 0.1){
        removeObject(*it);
        m_collisionManager->removeObject(*it);
        it->reset();
        *it = nullptr;
      }  
      
    }
  m_targets.remove(nullptr);
}

void Level::removeTarget(GameObject * g)
{
  for (auto& it : m_targets)
    {
      if (it.get() == g)
        {
          removeObject(g);
          m_collisionManager->removeObject(it);
          it.reset();
          it = nullptr;
        }  

    }
  /*  for(auto it = m_targets.begin(); it != m_targets.end(); ++it)
      {      
      if (it->get() == g)
      {
      removeObject(*it);
      m_collisionManager->removeObject(*it);
      it->reset();
      *it = nullptr;
      }  
      
      }*/
  m_targets.remove(nullptr);
}

void Level::updateScore()
{
  m_gui->getComponent<GUI>("GUI")->setScore(m_player->score);
}

void Level::updateLives()
{
  m_gui->getComponent<GUI>("GUI")->setLives(m_player->lives);
}

void Level::updateRow()
{
  m_gui->getComponent<GUI>("GUI")->setRow(m_player->row, m_player->multiplier);
}
