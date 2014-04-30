#include "FROG/Control/KeyboardButton.hpp"

namespace frog{

  KeyboardButton::KeyboardButton(sf::Keyboard::Key _code, 
                                 Trigger::ButtonTrigger _trigger, 
                                 bool _considering,
                                 bool _ctrl,
                                 bool _alt,
                                 bool _shift,
                                 bool _sys)
    : key(_code), trigger(_trigger), considering(_considering), 
      ctrl(_ctrl), alt(_alt), shift(_shift), sys(_sys)
  {
  }

  KeyboardButton::KeyboardButton(const KeyboardButton& other)
    : key(other.key), trigger(other.trigger), 
      considering(other.considering),
      ctrl(other.ctrl), alt(other.alt), shift(other.shift), sys(other.sys)
  {
  }

  KeyboardButton::KeyboardButton(const sf::Event::KeyEvent& ke,
                                 Trigger::ButtonTrigger _trigger,
                                 bool _considering)
    : key(ke.code), trigger(_trigger), considering(_considering), 
      ctrl(ke.control), alt(ke.alt), shift(ke.shift), sys(ke.system)
  {
  }

  KeyboardButton::~KeyboardButton()
  {
  }

  bool KeyboardButton::operator==(const KeyboardButton& other) const
  {
    return ( key == other.key 
             and trigger == other.trigger
             and considering == other.considering
             and ctrl == other.ctrl
             and alt == other.alt
             and shift == other.shift
             and sys == other.sys
             );
  }

  bool KeyboardButton::operator!=(const KeyboardButton& other) const
  {
    return ( not operator==(other) );
  }

}
