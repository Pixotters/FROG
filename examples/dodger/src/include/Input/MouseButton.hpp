#ifndef INPUT_MOUSEBUTTON_HPP
#define INPUT_MOUSEBUTTON_HPP

#include "Button.hpp"

class Controller;

namespace Input{

class MouseButton : virtual public Button
{

  //// attributes ////
protected : 
  sf::Mouse::Button m_button;

  //// operations ////
public:
  MouseButton(const sf::Mouse::Button&, 
              const Button::Trigger& = Button::PRESSED);
  virtual ~MouseButton();
  sf::Mouse::Button getButton() const;
  bool handle(Controller *);
};

}
#endif
