#ifndef FROG_CTRL_KEYBOARDBUTTON_HPP
#define FROG_CTRL_KEYBOARDBUTTON_HPP

#include "FROG/Control/Button.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    /*!
     * KeyboardButton is a real-time button pressed on a keyboard. 
     */
    class KeyboardButton : virtual public Button
    {

      //// attributes ////
    protected:
      sf::Keyboard::Key m_button;

      //// operations ////
    public:
      KeyboardButton(const sf::Keyboard::Key&);
      virtual ~KeyboardButton();
      sf::Keyboard::Key getButton() const;
      virtual bool check(ControlHandler *);
    };

  }

}

#endif
