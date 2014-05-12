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
  auto ctrl = ControlComponent::create(appInfo.eventList);
  obj->addComponent(ctrl, "CONTROL");
  createMapping();

  std::shared_ptr<sf::RectangleShape> r(new sf::RectangleShape(sf::Vector2f(OBJ_DIM, OBJ_DIM) ) );
  r->setFillColor(sf::Color::Red);
  r->setOutlineThickness(2);
  r->setOutlineColor(sf::Color::Black);
  obj->addComponent( RenderingComponent::create( r ), "RENDERING" );
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
