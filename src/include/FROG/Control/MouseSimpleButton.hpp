#ifndef CTRL_MOUSESIMPLEBUTTON_HPP
#define CTRL_MOUSESIMPLEBUTTON_HPP

#include "FROG/Control/MouseButton.hpp"
#include "FROG/Control/SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

namespace frog{

  namespace ctrl{

    class ControlHandler;

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
