#ifndef INPUT_MOUSESIMPLEBUTTON_HPP
#define INPUT_MOUSESIMPLEBUTTON_HPP

#include "MouseButton.hpp"
#include "SimpleButton.hpp"
#include <SFML/Window/Event.hpp>

class Controller;

namespace Input{

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
    bool handle(Controller *);

  };

}

#endif
