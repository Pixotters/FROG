#include "JoystickMover.hpp"

#include <iostream> // TODO remove

JoystickMover::JoystickMover(int _up, int _down, int _left, int _right,
                             sf::Joystick::Axis _x, sf::Joystick::Axis _y, 
                             unsigned short _deadzone,
                             unsigned int _joyId)
  : Component(), 
    up_velocity(_up), down_velocity(_down), 
    left_velocity(_left), right_velocity(_right),
    x(_x), y(_y), joystick_id(_joyId),
    deadzone(_deadzone)
{
  std::cout << "heavy ctor" << std::endl;
}

JoystickMover::JoystickMover(int _velocity,
                             sf::Joystick::Axis _x, sf::Joystick::Axis _y, 
                             unsigned short _deadzone,
                             unsigned int _joyId)
  : Component(), 
    up_velocity(_velocity), down_velocity(_velocity), 
    left_velocity(_velocity), right_velocity(_velocity),
    x(_x), y(_y), joystick_id(_joyId),
    deadzone(_deadzone)
{
  std::cout << "light ctor, deadzone = "<< \
    deadzone <<" / "<< _deadzone  << std::endl;
}

JoystickMover::~JoystickMover()
{

}

sf::Vector2f JoystickMover::getMovement() const
{
  float xmov = sf::Joystick::getAxisPosition(joystick_id, x);
  float ymov = sf::Joystick::getAxisPosition(joystick_id, y);
  std::cout << "mov : "<<xmov<<", "<<ymov<<" deadzone = "<<deadzone<<std::endl;
  if ( xmov > -deadzone and xmov < deadzone )
    {
      std::cout << "deadzone X" << std::endl;
      xmov = 0.0f;
    }
  if (ymov > -deadzone and ymov < deadzone )
    {
      std::cout << "deadzone Y" << std::endl;
      ymov = 0.0f;
    }
  xmov = (xmov > 0.0f) ? xmov*right_velocity/100.0f : xmov*left_velocity/100.0f;
  ymov = (ymov > 0.0f) ? ymov*down_velocity/100.0f : ymov*up_velocity/100.0f;
  return sf::Vector2f(xmov, ymov);
}

void JoystickMover::update(const frog::ComponentHolder& parent)
{
  std::cout << "Moving player to "<< getMovement().x << ","  \
            << getMovement().y << std::endl;
  parent.getComponent<frog::Transform>("TRANSFORM")->move( getMovement() );
}

