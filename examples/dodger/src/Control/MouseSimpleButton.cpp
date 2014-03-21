#include "Control/MouseSimpleButton.hpp"

#include "Control/Controller.hpp"

namespace ctrl{

  MouseSimpleButton::MouseSimpleButton(const sf::Mouse::Button& b, 
                                       const SimpleButton::Trigger& t)
    : MouseButton(b), SimpleButton(t)
  {
  }

  MouseSimpleButton::~MouseSimpleButton(){

  }

  bool MouseSimpleButton::occurred(Controller * c){
    return c->occurred(this);
  }

}
