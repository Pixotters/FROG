#include "FROG/Control/AnyKey.hpp"



namespace frog{

  AnyKey::AnyKey(Trigger::ButtonTrigger tr)
    : Input(), trigger(tr)
  {
    
  }

  AnyKey::~AnyKey()
  {
  }

  bool AnyKey::operator==(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type == sf::Event::KeyPressed;
    if (trigger == Trigger::RELEASED)
      return e.type == sf::Event::KeyReleased;
    return false;
  }

  bool AnyKey::operator!=(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type != sf::Event::KeyPressed;
    if (trigger == Trigger::RELEASED)
      return e.type != sf::Event::KeyReleased;
    return true;
  }

  AnyKey::PTR_AnyKey AnyKey::create(Trigger::ButtonTrigger tr)
  {
    return (PTR_AnyKey(new AnyKey(tr) ) );
  }

}
