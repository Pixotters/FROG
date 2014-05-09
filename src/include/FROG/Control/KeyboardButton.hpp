#ifndef FROG_KEYBOARDBUTTON_HPP
#define FROG_KEYBOARDBUTTON_HPP

#include "FROG/Control/ButtonTrigger.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  struct KeyboardButton : virtual public Input
  {

    typedef std::shared_ptr<KeyboardButton> PTR_KeyboardButton;

    sf::Keyboard::Key code;
    /// When does the input is detected: when pressed or released ?
    Trigger::ButtonTrigger trigger;
    /// Does the button key have to consider CTRL, ALT, SHIFT and SYS ?
    bool considering;
    bool ctrl;
    bool alt;
    bool shift;
    bool sys;

    KeyboardButton(sf::Keyboard::Key code, 
                   Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS, 
                   bool considering = false,
                   bool ctrl = false, 
                   bool alt = false, 
                   bool shift = false, 
                   bool sys = false);
    KeyboardButton(const KeyboardButton&);
    KeyboardButton(const sf::Event::KeyEvent&, 
                   Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS, 
                   bool considering = false);
    virtual ~KeyboardButton();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    bool operator==(const KeyboardButton&) const;
    bool operator!=(const KeyboardButton&) const;

  };

}
#endif
