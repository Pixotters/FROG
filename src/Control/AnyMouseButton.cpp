#include "FROG/Control/AnyMouseButton.hpp"

namespace frog{

  AnyMouseButton::AnyMouseButton(Trigger::ButtonTrigger tr)
    : Input(), trigger(tr)
  {
    
  }

  AnyMouseButton::~AnyMouseButton()
  {
  }

  bool AnyMouseButton::operator==(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type == sf::Event::MouseButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type == sf::Event::MouseButtonReleased;
    return false;
  }

  bool AnyMouseButton::operator!=(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type != sf::Event::MouseButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type != sf::Event::MouseButtonReleased;
    return true;
  }

  AnyMouseButton::PTR AnyMouseButton::create(Trigger::ButtonTrigger tr)
  {
    return (AnyMouseButton::PTR(new AnyMouseButton(tr) ) );
  }

}
