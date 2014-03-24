#include "Control/KeyboardSimpleButton.hpp"

#include "Control/ControlHandler.hpp"

namespace ctrl{

  KeyboardSimpleButton::KeyboardSimpleButton(const sf::Keyboard::Key& k, 
                                             const SimpleButton::Trigger& t)
    : KeyboardButton(k), SimpleButton(t)
  {
  }

  KeyboardSimpleButton::~KeyboardSimpleButton(){

  }

  bool KeyboardSimpleButton::check(ControlHandler * c){
    return c->check(this);
  }

}
