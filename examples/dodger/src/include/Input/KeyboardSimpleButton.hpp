#ifndef INPUT_KEYBOARDSIMPLEBUTTON_HPP
#define INPUT_KEYBOARDSIMPLEBUTTON_HPP

#include "KeyboardButton.hpp"
#include "SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

class Controller;

namespace Input{

  class KeyboardSimpleButton : virtual public KeyboardButton,
                               virtual public SimpleButton
  {

    //// attributes ////
  protected : 
    sf::Keyboard::Key m_button;
    unsigned int m_id;

    //// operations ////
  public:
    KeyboardSimpleButton(const sf::Keyboard::Key&, 
                         const SimpleButton::Trigger& = SimpleButton::PRESSED);
    virtual ~KeyboardSimpleButton();
    bool handle(Controller *);

  };

}

#endif
