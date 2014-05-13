#include "FROG/Control/JoystickMover.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  JoystickMover::JoystickMover(int _up, int _down, int _left, int _right,
                               sf::Joystick::Axis _x, sf::Joystick::Axis _y, 
                               unsigned int _joyId,
                               unsigned short _deadzone)
    : Component(), 
      up_velocity(_up), down_velocity(_down), 
      left_velocity(_left), right_velocity(_right),
      deadzone(_deadzone),
      joystick_id(_joyId), x(_x), y(_y)
  {
  }

  JoystickMover::JoystickMover(int _velocity,
                               sf::Joystick::Axis _x, sf::Joystick::Axis _y, 
                               unsigned int _joyId,
                               unsigned short _deadzone)
    : Component(), 
      up_velocity(_velocity), down_velocity(_velocity), 
      left_velocity(_velocity), right_velocity(_velocity),
      deadzone(_deadzone),
      joystick_id(_joyId), x(_x), y(_y)
  {
  }

  JoystickMover::~JoystickMover()
  {

  }

  sf::Vector2f JoystickMover::getMovement() const
  {
    float xmov = sf::Joystick::getAxisPosition(joystick_id, x);
    float ymov = sf::Joystick::getAxisPosition(joystick_id, y);
    if ( xmov > -deadzone and xmov < deadzone )
      {
        xmov = 0.0f;
      }
    if (ymov > -deadzone and ymov < deadzone )
      {
        ymov = 0.0f;
      }
    xmov = (xmov > 0.0f) ? xmov*right_velocity/100.0f : xmov*left_velocity/100.0f;
    ymov = (ymov > 0.0f) ? ymov*down_velocity/100.0f : ymov*up_velocity/100.0f;
    return sf::Vector2f(xmov, ymov);
  }

  void JoystickMover::update(const ComponentHolder& parent)
  {
    parent.getComponent<Transform>("TRANSFORM")->move( getMovement() );
  }

  JoystickMover::PTR JoystickMover::create(int up, int down, int left, int right, 
                                           sf::Joystick::Axis x,
                                           sf::Joystick::Axis y,
                                           unsigned int id,
                                           unsigned short deadzone)
  {
    return PTR(new JoystickMover(up, down, left, right, x, y, id, deadzone) );
  }

  JoystickMover::PTR JoystickMover::create(int velocity,
                                           sf::Joystick::Axis x,
                                           sf::Joystick::Axis y,
                                           unsigned int id,
                                           unsigned short deadzone
                                           )
  {
    return PTR(new JoystickMover(velocity, x, y, id, deadzone) );
  }

}
