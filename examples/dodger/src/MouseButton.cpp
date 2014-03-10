#include "Input/MouseButton.hpp"

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


}
