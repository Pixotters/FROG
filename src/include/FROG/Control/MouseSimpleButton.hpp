#ifndef FROG_CTRL_MOUSESIMPLEBUTTON_HPP
#define FROG_CTRL_MOUSESIMPLEBUTTON_HPP

#include "FROG/Control/MouseButton.hpp"
#include "FROG/Control/SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

    /*!
     * MouseSimpleButton is a one-time button pressed on a keyboard. 
     */
    class MouseSimpleButton : virtual public MouseButton,
                              virtual public SimpleButton
    {

      //// attributes ////
    protected : 
      sf::Mouse::Button m_button;

      //// operations ////
    public:
      MouseSimpleButton(const sf::Mouse::Button&, 
                        const SimpleButton::Trigger& = SimpleButton::PRESSED);
      virtual ~MouseSimpleButton();
      bool check(ControlHandler *);

    };

  }

}

#endif
