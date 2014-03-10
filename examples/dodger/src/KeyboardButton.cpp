#include "Input/KeyboardButton.hpp"

namespace Input{

  KeyboardButton::KeyboardButton(const sf::Keyboard::Key& k, 
                                 const Button::Trigger& t)
    :Button(t), m_button(k)
  {
    
  }

  KeyboardButton::~KeyboardButton()
  {

  }

  sf::Keyboard::Key KeyboardButton::getButton() const
  {
    return m_button;
  }

}
