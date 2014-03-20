#include "JoystickMove.hpp"

#include <iostream> // TODO remove

#define DEADZONE 25

JoystickMove::JoystickMove(GameObject * const go,
                           ctrl::Controller * const c,
                           const unsigned int& id)
  : Command(), m_gameobject(go), m_controller(c)
{

}

JoystickMove::~JoystickMove(){}

bool JoystickMove::execute()
{
  
  float x = 0.f, y = 0.f;
  x = m_controller->getJoystickAxis(m_id, sf::Joystick::X) / 10.f;
  y = m_controller->getJoystickAxis(m_id, sf::Joystick::Y) / 10.f;
  std::cout << "joystick : "<<x<<","<<y<<std::endl;
  if( x > DEADZONE || y > DEADZONE || x < -DEADZONE || y < -DEADZONE){
      std::cout << "moved player"<<std::endl;
    float px = m_gameobject->getTransform().getPosition().x+x;
    float py = m_gameobject->getTransform().getPosition().y+y;
    if( px < 0){
      px = 0;
    }
    if( py < 0){
      py = 0;
    }
    if( px > 800){
      px = 800;
    }
    if(py > 600){
      py = 600;
    }      
    m_gameobject->getTransform().setPosition(px, py);  

    return true;
  }
  return false;
}
