#ifndef FROG_CTRL_KEYBOARDSIMPLEBUTTON_HPP
#define FROG_CTRL_KEYBOARDSIMPLEBUTTON_HPP

#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    /*!
     * KeyboardSimpleButton is a one-time button pressed on a keyboard. 
     */
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
      bool check(ControlHandler *);

    };

  }

}

#endif
