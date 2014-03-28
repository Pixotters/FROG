#ifndef CTRL_MOUSEBUTTON_HPP
#define CTRL_MOUSEBUTTON_HPP

#include "Control/Button.hpp"

#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    class MouseButton : virtual public Button
    {

      //// attributes ////
    protected : 
      sf::Mouse::Button m_button;

      //// operations ////
    public:
      MouseButton(const sf::Mouse::Button&);
      virtual ~MouseButton();
      sf::Mouse::Button getButton() const;
      bool check(ControlHandler *);
    };

  }

}

#endif
