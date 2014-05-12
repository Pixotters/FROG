#include <FROG/App.hpp>
#include <FROG/GameObject.hpp>
#include <FROG/Collision/BoxCollider.hpp>
#include <FROG/Collision/RoundCollider.hpp>
#include <FROG/Collision/LSAP.hpp>
#include <FROG/Control.hpp>
#include <FROG/Function.hpp>

#include "Demo_Colliders.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream> // TODO remove

#define OBJ_DIM 64

using namespace frog;

MainState::MainState(AppInfo& _appinfo)
  : Scene(_appinfo), 
    mode(0), 
    collisions(0),
    obj(new GameObject), 
    obstacle(new GameObject),
    collider_object(new GameObject)
{
}

MainState::~MainState()
{
}


void MainState::enter()
{
  initObj_rectangle();
  initCollider();
  initObstacle();
  
  addObject(collider_object);
  addObject(obj);
  addObject(obstacle);
  m_collisionManager.addObject(obj);
  m_collisionManager.addObject(obstacle);
  changeMap();
}


void MainState::initObj_rectangle()
{
  obj->transform->layer = 2;
  auto ctrl = ControlComponent::create(appInfo.eventList);
  obj->addComponent(ctrl, "CONTROL");
  createMapping();
  std::shared_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(OBJ_DIM, OBJ_DIM) ) );
  r->setFillColor(sf::Color(255,0,0,100) );
  r->setOutlineThickness(2);
  r->setOutlineColor(sf::Color::Black);
  obj->addComponent( RenderingComponent::create( r ), "RENDERING" );
  obj->getComponent<Transform>("TRANSFORM")->setPosition(100, 70);
  obj->getComponent<Transform>("TRANSFORM")->setOrigin(OBJ_DIM/2, OBJ_DIM/2);  
  
  auto collider = BoxCollider::create(sf::Vector2f(OBJ_DIM, OBJ_DIM) );
  auto collision = [this](Collision c){
    collisions++;
    std::cout << "collisions : " << collisions << std::endl;
  };
  collider->setScript(collision);
  obj->addComponent( collider, 
                     "COLLIDER");
}

void MainState::initObj_circle()
{
  obj->transform->layer = 2;
  auto ctrl = ControlComponent::create(appInfo.eventList);
  obj->addComponent(ctrl, "CONTROL");
  createMapping();
  std::shared_ptr<sf::CircleShape> r(new sf::CircleShape(OBJ_DIM) );
  r->setFillColor(sf::Color(255,0,0,100) );
  r->setOutlineThickness(2);
  r->setOutlineColor(sf::Color::Black);
  obj->addComponent( RenderingComponent::create( r ), "RENDERING" );
  obj->getComponent<Transform>("TRANSFORM")->setPosition(100, 70);
  obj->getComponent<Transform>("TRANSFORM")->setOrigin(OBJ_DIM, OBJ_DIM);  
  
  auto collider = RoundCollider::create(OBJ_DIM);
  auto collision = [this](Collision c){
    collisions++;
    std::cout << "collisions : " << collisions << std::endl;
  };
  collider->setScript(collision);
  obj->addComponent( collider, 
                     "COLLIDER");
}

void MainState::initCollider()
{
  std::shared_ptr<sf::RectangleShape> r2(new sf::RectangleShape(sf::Vector2f(OBJ_DIM, 10) ) );
  r2->setFillColor(sf::Color::Yellow);
  collider_object->addComponent( RenderingComponent::create( r2 ), "RENDERING" );
  //  collider_object->transform = obj->transform;
}

void MainState::initObstacle()
{
  obstacle->transform->setPosition(20, 40);
  obstacle->addComponent(BoxCollider::create(sf::Vector2f(20,100)),
                         "COLLIDER");
  std::shared_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(20, 100) ) );
  r->setFillColor(sf::Color::Green);
  obstacle->addComponent(RenderingComponent::create(r), "RENDERING");
}

void MainState::exit()
{
  delete mapping_move;
  delete mapping_resize;
  delete mapping_rotate;
}

void MainState::preupdate()
{
  std::shared_ptr<sf::RectangleShape> rect(new sf::RectangleShape() );
  rect->setFillColor(sf::Color(0,0,255,100) );
  try{
    auto fr = obj->getComponent<BoxCollider>("COLLIDER")->getBoundingBox();
      rect->setSize( sf::Vector2f(fr.width, fr.height) );
      rect->setPosition(fr.left, fr.top );
  }catch(std::logic_error e)
    {
      try{
        auto fr = obj->getComponent<RoundCollider>("COLLIDER")->getBoundingBox();
        rect->setSize( sf::Vector2f(fr.width, fr.height) );
        rect->setPosition(fr.left, fr.top );
      }catch(std::logic_error e)
        {

        }
    }
  // DON'T DO THAT
  m_renderer.removeObject(collider_object);
  collider_object->removeComponent("RENDERING");
  collider_object->addComponent(RenderingComponent::create(rect),
                                "RENDERING");
  m_renderer.addObject(collider_object);
  //
}

void MainState::postupdate()
{
  m_collisionManager.update();
 }

void MainState::createMapping()
{
  mapping_move = new ControlComponent::INPUT_MAP;
  mapping_resize = new ControlComponent::INPUT_MAP;
  mapping_rotate = new ControlComponent::INPUT_MAP;
  auto z_key = KeyboardButton::create(sf::Keyboard::Z);
  auto q_key = KeyboardButton::create(sf::Keyboard::Q);
  auto s_key = KeyboardButton::create(sf::Keyboard::S);
  auto d_key = KeyboardButton::create(sf::Keyboard::D);
  auto a_key = KeyboardButton::create(sf::Keyboard::A);
  auto e_key = KeyboardButton::create(sf::Keyboard::E);
  auto space_key = KeyboardButton::create(sf::Keyboard::Space,
                                          Trigger::PRESSED);
  auto resize_x_plus = Resize::create(obj, 0.009, 0);
  auto resize_x_minus = Resize::create(obj, -0.009, 0);
  auto resize_y_plus = Resize::create(obj, 0, 0.009);
  auto resize_y_minus = Resize::create(obj, 0, -0.009);
  auto move_x_plus = Move::create(obj, 1, 0);
  auto move_x_minus = Move::create(obj, -1, 0);
  auto move_y_plus = Move::create(obj, 0, 1);
  auto move_y_minus = Move::create(obj, 0, -1);
  auto rot_right = Rotate::create(obj, 1);
  auto rot_left = Rotate::create(obj, -1);
  auto changemode = Function::create( [this](){
      mode = (mode == 2) ? 0 : mode+1;
      changeMap();
    });
  mapping_move->emplace(z_key, move_y_minus);
  mapping_move->emplace(q_key, move_x_minus);
  mapping_move->emplace(s_key, move_y_plus);
  mapping_move->emplace(d_key, move_x_plus);
  mapping_resize->emplace(z_key, resize_y_plus);
  mapping_resize->emplace(q_key, resize_x_minus);
  mapping_resize->emplace(s_key, resize_y_minus);
  mapping_resize->emplace(d_key, resize_x_plus);
  mapping_rotate->emplace(e_key, rot_right);
  mapping_rotate->emplace(a_key, rot_left);
  auto ctrl = obj->getComponent<ControlComponent>("CONTROL");
  ctrl->bind(space_key, changemode, 0);
}

void MainState::changeMap()
{
  auto ctrl = obj->getComponent<ControlComponent>("CONTROL");
  std::cout << "change mode to ";
  switch(mode)
    {
    case 1:
      ctrl->changeMap(*mapping_resize, 1);
      std::cout << "RESIZE : Z,Q,S,D";
      break;
    case 2:
      ctrl->changeMap(*mapping_rotate, 1);
      std::cout << "ROTATE : A,E";
      break;
    default:
      ctrl->changeMap(*mapping_move, 1);
      std::cout << "MOVE : Z,Q,S,D";
      break;
    }
  std::cout << std::endl;
}




int main()
{
  frog::App demo("FROG - Colliders demo");
  demo.start( new MainState( demo.appInfo ) );
}
