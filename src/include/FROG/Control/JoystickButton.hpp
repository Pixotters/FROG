#ifndef FROG_JOYSTICKBUTTON_HPP
#define FROG_JOYSTICKBUTTON_HPP

#include "FROG/Control/ButtonTrigger.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>

namespace frog{

  struct JoystickButton : virtual public Input
  {

    unsigned int id;
    unsigned int code;
    /// When does the input is detected: when pressed or released ?
    Trigger::ButtonTrigger trigger;

    JoystickButton(unsigned int code, 
                   Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS,
                   unsigned int id = 0);
    JoystickButton(const JoystickButton&);
    JoystickButton(const JoystickButton&, unsigned int id);
    JoystickButton(const sf::Event::JoystickButtonEvent&, 
                   Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    virtual ~JoystickButton();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    virtual bool operator==(const sf::Event::JoystickButtonEvent&) const;
    virtual bool operator!=(const sf::Event::JoystickButtonEvent&) const;
    bool operator==(const JoystickButton&) const;
    bool operator!=(const JoystickButton&) const;

  };

}
#endif