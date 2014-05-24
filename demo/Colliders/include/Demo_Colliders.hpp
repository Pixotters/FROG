#ifndef FROG_DEMO_COLLIDERS
#define FROG_DEMO_COLLIDERS

#include <FROG/Rendering/Scene.hpp>
#include <FROG/Core/AppInfo.hpp>
#include <FROG/Core/GameObject.hpp>
#include <FROG/Control/Command.hpp>
#include <FROG/Core/Transform.hpp>
#include <FROG/Control/ControlComponent.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

class MainState : virtual public frog::Scene
{

public:
  int mode; // mode MOVE, RESIZE or ROTATE
  long collisions; // number of frames when there was collision

private:
  frog::GameObject::PTR obj;
  frog::GameObject::PTR obstacle;
  frog::GameObject::PTR collider_object;
  frog::ControlComponent::INPUT_MAP * mapping_move;
  frog::ControlComponent::INPUT_MAP * mapping_resize;
  frog::ControlComponent::INPUT_MAP * mapping_rotate;
  frog::LSAP m_collisionManager;

public:
  MainState(frog::AppInfo&);
  virtual ~MainState();
  virtual void enter();
  virtual void preupdate();
  virtual void postupdate();
  virtual void exit();
  void changeMap();

private:
  void initObj_rectangle();
  void initObj_circle();
  void initCollider();
  void initObstacle();
  void createMapping();

};

class Resize : virtual public frog::Command
{

public:
  typedef std::shared_ptr<Resize> PTR;

private:
  std::shared_ptr<frog::GameObject> obj;
  sf::Vector2f amount;

public:
  Resize(std::shared_ptr<frog::GameObject> g, float x, float y)
    : frog::Command(), obj(g), amount(x, y){ };
  virtual ~Resize(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    t->setScale( t->getScale()+amount); 
  };
  static PTR create(std::shared_ptr<frog::GameObject> g, float x, float y)
  {
    return PTR( new Resize(g, x, y) );
  };
};

class Move : virtual public frog::Command
{

public:
  typedef std::shared_ptr<Move> PTR;

private:
  std::shared_ptr<frog::GameObject> obj;
  sf::Vector2f amount;

public:
  Move(std::shared_ptr<frog::GameObject> g, float x, float y)
    : frog::Command(), obj(g), amount(x, y){ };
  virtual ~Move(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    t->move(amount); 
  };
  static PTR create(std::shared_ptr<frog::GameObject> g, float x, float y)
  {
    return PTR( new Move(g, x, y) );
  };

};

class Rotate: virtual public frog::Command
{

public:
  typedef std::shared_ptr<Rotate> PTR;

private:
  std::shared_ptr<frog::GameObject> obj;
  float amount;

public:
  Rotate(std::shared_ptr<frog::GameObject> g, float a)
    : frog::Command(), obj(g), amount(a){ };
  virtual ~Rotate(){};
  virtual void execute(){ 
    auto t = obj->getComponent<frog::Transform>("TRANSFORM");
    t->rotate(amount); 
  };
  static PTR create(std::shared_ptr<frog::GameObject> g, float a)
  {
    return PTR( new Rotate(g, a) );
  };


};


#endif
