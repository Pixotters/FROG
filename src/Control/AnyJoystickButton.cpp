#include "FROG/Control/AnyJoystickButton.hpp"

namespace frog{

  AnyJoystickButton::AnyJoystickButton(Trigger::ButtonTrigger tr)
    : Input(), trigger(tr)
  {
    
  }

  AnyJoystickButton::~AnyJoystickButton()
  {
  }

  bool AnyJoystickButton::operator==(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type == sf::Event::JoystickButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type == sf::Event::JoystickButtonReleased;
    return false;
  }

  bool AnyJoystickButton::operator!=(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type != sf::Event::JoystickButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type != sf::Event::JoystickButtonReleased;
    return true;
  }

  AnyJoystickButton::PTR AnyJoystickButton::create(Trigger::ButtonTrigger tr)
  {
    return (AnyJoystickButton::PTR(new AnyJoystickButton(tr) ) );
  }

}
