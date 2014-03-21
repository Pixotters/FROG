#include "Control/MouseButton.hpp"

#include "Control/Controller.hpp"

namespace ctrl{

  MouseButton::MouseButton(const sf::Mouse::Button& b)
    : Button(), m_button(b) {

  }

  MouseButton::~MouseButton(){

  }

  sf::Mouse::Button MouseButton::getButton() const{
    return m_button;
  }

  bool MouseButton::check(Controller * c)
  {
    return c->check(this);
  }

}
