
#include "Level.hpp"

#include "Enemy.hpp"
#include "Target.hpp"

#include "Control.hpp"
#include "Translator.hpp"

#include "App.hpp"

#include "Random.hpp"

#include "MovePlayer.hpp"
#include "JoystickMove.hpp"
#include "Bomb.hpp"

#include <iostream> // TODO remove

class Collider : virtual public ActionManager{

private:
  Player * m_player;
  std::list<Target *> * m_targets;

public:
  Collider(Player * p, std::list<Target *> * t) 
    : m_player(p), m_targets(t){}

  virtual void onCollision(Collisionable * a, Collisionable * b){
       
    Player * p;
    Target * t1;
    Target * t2;
    if(
       ( (p = dynamic_cast<Player *>(a) )
         && (t2 = dynamic_cast<Target *>(b) ) )
       //      ||( (p = dynamic_cast<Player *>(b) )
       //          && (t2 = dynamic_cast<Target *>(a) ) )
       ){
      std::cout << "converted p-t"<<std::endl;
      onCollision(p, t2);
    }
    if( (t1 = dynamic_cast<Target *>(a) )
        && (t2 = dynamic_cast<Target *>(b) ) ){
      onCollision(t1, t2);
    }
  }

  void onCollision(Player * a, Target * b){
    std::cout << "collision player-target "<< std::endl;
    m_targets -> remove(b);
  }

  void onCollision(Target * a, Target * b){
    std::cout << "collision target-target "<< std::endl;
    //    m_targets -> remove(b);
  }
  
  virtual void onSeparation(Collisionable * a, Collisionable * b){

  }

};


Level::Level()
  : Scene()
{ 
  m_player = new Player;
  m_gameObjects.push_back(m_player);
  auto moveleft = new MovePlayer(m_player, -4, 0);
  auto moveright = new MovePlayer(m_player, 4, 0);
  auto moveup = new MovePlayer(m_player, 0, -8);
  auto movedown = new MovePlayer(m_player, 0, 8);
  std::cout << "phase1" <<std::endl;
  std::cout << "phase1.1" <<std::endl;

  auto qkey = new ctrl::KeyboardButton(sf::Keyboard::Q);
  auto dkey = new ctrl::KeyboardButton(sf::Keyboard::D);
  auto zkey = new ctrl::KeyboardButton(sf::Keyboard::Z);
  auto skey = new ctrl::KeyboardButton(sf::Keyboard::S);
  std::cout << "phase1.2" <<std::endl;
  m_actionManager.set(qkey, moveleft );    
  m_actionManager.set(dkey, moveright );
  m_actionManager.set(zkey, moveup );  
  m_actionManager.set(skey,  movedown ); 
  std::cout << "phase1.3" <<std::endl;
  m_controller.suscribe(zkey);
  m_controller.suscribe(dkey);
  m_controller.suscribe(qkey);
  m_controller.suscribe(skey);
  std::cout << "phase1.4" <<std::endl;
  /* m_actionManager.set(new ctrl::JoystickButton(XBOX::X), moveleft );    

  m_actionManager.set(new ctrl::JoystickButton(XBOX::B), moveright );

  m_actionManager.set(new ctrl::JoystickButton(XBOX::Y), moveup );    

  m_actionManager.set(new ctrl::JoystickButton(XBOX::A), movedown );

  m_actionManager.set(new ctrl::MouseButton(sf::Mouse::Left),
                       new Bomb(m_ennemies) );

  m_actionManager.set(new ctrl::MouseSimpleButton(sf::Mouse::Right),
                       new Bomb(m_ennemies) );
  m_actionManager.set(new ctrl::JoystickSimpleButton(XBOX::HOME), 
  new Bomb(m_ennemies) );*/
  std::cout << "phase2" <<std::endl;
  Collider * am = new Collider(m_player, &m_targets);
  m_collider = new SAPList(am);  
  m_collider->addObject(m_player);
  std::cout << "player is "<<m_player<<std::endl;
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
  //  std::cout<< "handling..." << std::endl;
    handleCommands(&m_controller, &m_actionManager);
  //  JoystickMove * jm = new JoystickMove(m_player, &m_controller);
  //  jm->execute();
  //  delete jm;  
  //  std::cout<< "handled..." << std::endl;
  m_collider->updateObject(m_player);
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
  Enemy * e = new Enemy;
  e->getTransform().setPosition(Random::get(100, 700), 50);
  m_ennemies.push_back(e );
}

void Level::spawnTarget()
{
  Target * e = new Target;
  e->getTransform().setPosition(Random::get(100, 700), Random::get(50, 550) );
  m_targets.push_back(e);
  m_collider->addObject(e);
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
      m_collider->updateObject(*it);
      if((*it)->getTransform().getPosition().x > 800 
         || (*it)->getTransform().getPosition().y > 600 
         || (*it)->getTransform().getPosition().x < -32
         || (*it)->getTransform().getPosition().y < -32){
        m_collider->removeObject(*it);
        delete (*it);
        *it = nullptr;
      }  

    }
  m_targets.remove(nullptr);
}


void Level::movePlayer(const short& x)
{
  m_player->getTransform().move(x, 0);
}
