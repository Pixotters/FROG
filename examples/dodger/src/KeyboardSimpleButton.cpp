#include "Input/KeyboardSimpleButton.hpp"

#include "Controller.hpp"

namespace Input{

  KeyboardSimpleButton::KeyboardSimpleButton(const sf::Keyboard::Key& k, 
                                             const SimpleButton::Trigger& t)
    : KeyboardButton(k), SimpleButton(t)
  {
  }

  KeyboardSimpleButton::~KeyboardSimpleButton(){

  }

  bool KeyboardSimpleButton::handle(Controller * c){
    return c->handle(this);
  }

}
