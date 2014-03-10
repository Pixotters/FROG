#ifndef INPUT_MOUSEBUTTON_HPP
#define INPUT_MOUSEBUTTON_HPP

#include "Button.hpp"

namespace Input{

class MouseButton : virtual public Button
{

  //// attributes ////
protected : 
  sf::Mouse::Button m_button;

  //// operations ////
public:
  MouseButton(const sf::Mouse::Button&, const Button::Trigger&);
  virtual ~MouseButton();
  sf::Mouse::Button getButton() const;
};

}
#endif
