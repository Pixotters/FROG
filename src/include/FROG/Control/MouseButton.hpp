#ifndef FROG_CTRL_MOUSEBUTTON_HPP
#define FROG_CTRL_MOUSEBUTTON_HPP

#include "FROG/Control/Button.hpp"

#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    /*!
     * MouseButton is a real-time button pressed on a keyboard. 
     */
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
