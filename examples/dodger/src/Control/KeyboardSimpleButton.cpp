#include "Control/KeyboardSimpleButton.hpp"

#include "Control/Controller.hpp"

namespace ctrl{

  KeyboardSimpleButton::KeyboardSimpleButton(const sf::Keyboard::Key& k, 
                                             const SimpleButton::Trigger& t)
    : KeyboardButton(k), SimpleButton(t)
  {
  }

  KeyboardSimpleButton::~KeyboardSimpleButton(){

  }

  bool KeyboardSimpleButton::check(Controller * c){
    return c->check(this);
  }

}
