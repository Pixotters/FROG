#include <FROG/App.hpp>
#include <FROG/GameObject.hpp>
#include <FROG/Collision/Collider.hpp>
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
  : Scene(_appinfo), mode(0), obj(new GameObject)
{
}

MainState::~MainState()
{
}


void MainState::enter()
{
  std::shared_ptr<ControlComponent> ctrl( new ControlComponent(appInfo.eventList) );
  obj->addComponent(ctrl, "CONTROL");
  createMapping();

  std::shared_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(OBJ_DIM, OBJ_DIM) ) );
  r->setFillColor(sf::Color::Red);
  r->setOutlineThickness(2);
  r->setOutlineColor(sf::Color::Black);
  obj->addComponent(new RenderingComponent( r ), "RENDERING" );
  obj->getComponent<Transform>("TRANSFORM")->setPosition(100, 100);
  obj->getComponent<Transform>("TRANSFORM")->setOrigin(OBJ_DIM/2, OBJ_DIM/2);
  addObject(obj);
  changeMap();
}

void MainState::exit()
{
  delete mapping_move;
  delete mapping_resize;
  delete mapping_rotate;
}


void MainState::createMapping()
{
  mapping_move = new ControlComponent::INPUT_MAP;
  mapping_resize = new ControlComponent::INPUT_MAP;
  mapping_rotate = new ControlComponent::INPUT_MAP;
  std::shared_ptr<Input> z_key(new KeyboardButton(sf::Keyboard::Z) );
  std::shared_ptr<Input> q_key(new KeyboardButton(sf::Keyboard::Q) );
  std::shared_ptr<Input> s_key(new KeyboardButton(sf::Keyboard::S) );
  std::shared_ptr<Input> d_key(new KeyboardButton(sf::Keyboard::D) );
  std::shared_ptr<Input> a_key(new KeyboardButton(sf::Keyboard::A) );
  std::shared_ptr<Input> e_key(new KeyboardButton(sf::Keyboard::E) );
  std::shared_ptr<Input> space_key(new KeyboardButton(sf::Keyboard::Space,
                                                      Trigger::PRESSED) );
  std::shared_ptr<Resize> resize_x_plus(new Resize(obj, 0.009, 0) );
  std::shared_ptr<Resize> resize_x_minus(new Resize(obj, -0.009, 0) );
  std::shared_ptr<Resize> resize_y_plus(new Resize(obj, 0, 0.009) );
  std::shared_ptr<Resize> resize_y_minus(new Resize(obj, 0, -0.009) );
  std::shared_ptr<Move> move_x_plus(new Move(obj, 1, 0) );
  std::shared_ptr<Move> move_x_minus(new Move(obj, -1, 0) );
  std::shared_ptr<Move> move_y_plus(new Move(obj, 0, 1) );
  std::shared_ptr<Move> move_y_minus(new Move(obj, 0, -1) );
  std::shared_ptr<Rotate> rot_right(new Rotate(obj, 1) );
  std::shared_ptr<Rotate> rot_left(new Rotate(obj, -1) );
  auto changemode = Function::create( [this](){
      mode = (mode == 2) ? 0 : mode+1;
      changeMap();
    });
  mapping_move->emplace(z_key, move_y_minus);
  mapping_move->emplace(q_key, move_x_minus);
  mapping_move->emplace(s_key, move_y_plus);
  mapping_move->emplace(d_key, move_x_plus);
  mapping_resize->emplace(z_key, resize_y_minus);
  mapping_resize->emplace(q_key, resize_x_minus);
  mapping_resize->emplace(s_key, resize_y_plus);
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
      std::cout << "RESIZE ";
      break;
    case 2:
      ctrl->changeMap(*mapping_rotate, 1);
      std::cout << "ROTATE ";
      break;
    default:
      ctrl->changeMap(*mapping_move, 1);
      std::cout << "MOVE ";
      break;
    }
  std::cout << std::endl;
}




int main()
{
  frog::App demo("FROG - Colliders demo");
  demo.start( new MainState( demo.appInfo ) );
}
