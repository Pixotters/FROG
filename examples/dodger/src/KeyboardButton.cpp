#include "Input/KeyboardButton.hpp"

#include "Controller.hpp"

namespace Input{

  KeyboardButton::KeyboardButton(const sf::Keyboard::Key& k)
    :Button(), m_button(k)
  {
    
  }

  KeyboardButton::~KeyboardButton()
  {

  }

  sf::Keyboard::Key KeyboardButton::getButton() const
  {
    return m_button;
  }

  bool KeyboardButton::handle(Controller * c)
  {
    return c->handle(this);
  }

}
