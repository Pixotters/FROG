#ifndef CTRL_KEYBOARDBUTTON_HPP
#define CTRL_KEYBOARDBUTTON_HPP

#include "Control/Button.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

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
