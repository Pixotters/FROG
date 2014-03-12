#ifndef INPUT_KEYBOARDBUTTON_HPP
#define INPUT_KEYBOARDBUTTON_HPP

#include "Button.hpp"

class Controller;

namespace Input{

class KeyboardButton : virtual public Button
{

  //// attributes ////
protected:
  sf::Keyboard::Key m_button;

  //// operations ////
public:
  KeyboardButton(const sf::Keyboard::Key&, 
                 const Button::Trigger& = Button::PRESSED);
  virtual ~KeyboardButton();
  sf::Keyboard::Key getButton() const;
  virtual bool handle(Controller *);
};

}

#endif
