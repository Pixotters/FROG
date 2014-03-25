#include "Control/MouseButton.hpp"

#include "Control/ControlHandler.hpp"

namespace frog{

  namespace ctrl{

    MouseButton::MouseButton(const sf::Mouse::Button& b)
      : Button(), m_button(b) {

    }

    MouseButton::~MouseButton(){

    }

    sf::Mouse::Button MouseButton::getButton() const{
      return m_button;
    }

    bool MouseButton::check(ControlHandler * c)
    {
      return c->check(this);
    }

  }

}
