#include "Input/MouseButton.hpp"

#include "Controller.hpp"

namespace Input{

  MouseButton::MouseButton(const sf::Mouse::Button& b, 
                           const Button::Trigger& t)
    : Button(t), m_button(b) {

  }

  MouseButton::~MouseButton(){

  }

  sf::Mouse::Button MouseButton::getButton() const{
    return m_button;
  }

  bool MouseButton::handle(Controller * c)
  {
    return c->handle(this);
  }

}
