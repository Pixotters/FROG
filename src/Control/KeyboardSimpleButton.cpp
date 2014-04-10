#include "FROG/Control/KeyboardSimpleButton.hpp"

#include "FROG/Control/ControlHandler.hpp"

namespace frog{

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

}
