#ifndef FROG_DEMO_COLLIDERS
#define FROG_DEMO_COLLIDERS

#include "FROG/Scene.hpp"
#include "FROG/AppInfo.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Command.hpp"
#include "FROG/Transform.hpp"
#include "FROG/Control/ControlComponent.hpp"
#include <SFML/System/Vector2.hpp>

#include <memory>

class MainState : virtual public frog::Scene
{

public:
  int mode; // mode MOVE, RESIZE or ROTATE

private:
  std::shared_ptr<frog::GameObject> obj;
  frog::ControlComponent::INPUT_MAP * mapping_move;
  frog::ControlComponent::INPUT_MAP * mapping_resize;
  frog::ControlComponent::INPUT_MAP * mapping_rotate;
  frog::LSAP m_collisionManager;

public:
  MainState(frog::AppInfo&);
  virtual ~MainState();
  virtual void enter();
  virtual void exit();
  void changeMap();

private:
  void createMapping();

};

class Resize : virtual public frog::Command
{
private:
  std::shared_ptr<frog::GameObject> obj;
  sf::Vector2f amount;

public:
  Resize(std::shared_ptr<frog::GameObject> g, float x, float y)
    : frog::Command(), obj(g), amount(x, y){ };
  virtual ~Resize(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    std::cout << "Previous size : " << t->getScale().x \
              << ":" << t->getScale().y << std::endl;
    t->setScale( t->getScale()+amount); 
    std::cout << "New size : " << t->getScale().x \
              << ":" << t->getScale().y << std::endl;
    
  };
};

class Move : virtual public frog::Command
{
private:
  std::shared_ptr<frog::GameObject> obj;
  sf::Vector2f amount;

public:
  Move(std::shared_ptr<frog::GameObject> g, float x, float y)
    : frog::Command(), obj(g), amount(x, y){ };
  virtual ~Move(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    std::cout << "Previous position : " << t->getPosition().x \
              << "," << t->getPosition().y << std::endl;
    t->move(amount); 
    std::cout << "New position : " << t->getPosition().x \
              << "," << t->getPosition().y << std::endl;
    
  };

};

class Rotate: virtual public frog::Command
{
private:
  std::shared_ptr<frog::GameObject> obj;
  float amount;

public:
  Rotate(std::shared_ptr<frog::GameObject> g, float a)
    : frog::Command(), obj(g), amount(a){ };
  virtual ~Rotate(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    std::cout << "Previous rotation : " << t->getRotation() << std::endl; 
    t->rotate(amount); 
    std::cout << "New rotation : " << t->getRotation() << std::endl; 
    
  };

};


#endif
