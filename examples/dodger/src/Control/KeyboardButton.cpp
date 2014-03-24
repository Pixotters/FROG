#include "Control/KeyboardButton.hpp"

#include "Control/ControlHandler.hpp"

namespace ctrl{

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

  bool KeyboardButton::check(ControlHandler * c)
  {
    return c->check(this);
  }

}
