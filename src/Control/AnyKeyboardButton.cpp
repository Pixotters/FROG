#include "FROG/Control/AnyKeyboardButton.hpp"

namespace frog{

  AnyKeyboardButton::AnyKeyboardButton(Trigger::ButtonTrigger tr)
    : Input(), trigger(tr)
  {
    
  }

  AnyKeyboardButton::~AnyKeyboardButton()
  {
  }

  bool AnyKeyboardButton::operator==(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type == sf::Event::JoystickButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type == sf::Event::JoystickButtonReleased;
    return false;
  }

  bool AnyKeyboardButton::operator!=(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type != sf::Event::JoystickButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type != sf::Event::JoystickButtonReleased;
    return true;
  }

  AnyKeyboardButton::PTR AnyKeyboardButton::create(Trigger::ButtonTrigger tr)
  {
    return (AnyKeyboardButton::PTR(new AnyKeyboardButton(tr) ) );
  }

}
