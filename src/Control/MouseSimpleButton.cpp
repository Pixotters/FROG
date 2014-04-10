#include "FROG/Control/MouseSimpleButton.hpp"

#include "FROG/Control/ControlHandler.hpp"

namespace frog{

  namespace ctrl{

    MouseSimpleButton::MouseSimpleButton(const sf::Mouse::Button& b, 
                                         const SimpleButton::Trigger& t)
      : MouseButton(b), SimpleButton(t)
    {
    }

    MouseSimpleButton::~MouseSimpleButton(){

    }

    bool MouseSimpleButton::check(ControlHandler * c){
      return c->check(this);
    }

  }

}
