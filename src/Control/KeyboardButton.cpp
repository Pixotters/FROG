#include "FROG/Control/KeyboardButton.hpp"

#include <iostream> // TODO remove

namespace frog{

  KeyboardButton::KeyboardButton(sf::Keyboard::Key _code, 
                                 Trigger::ButtonTrigger _trigger, 
                                 bool _considering,
                                 bool _ctrl,
                                 bool _alt,
                                 bool _shift,
                                 bool _sys)
    : code(_code), trigger(_trigger), considering(_considering), 
      ctrl(_ctrl), alt(_alt), shift(_shift), sys(_sys)
  {
  }

  KeyboardButton::KeyboardButton(const KeyboardButton& other)
    : code(other.code), trigger(other.trigger), 
      considering(other.considering),
      ctrl(other.ctrl), alt(other.alt), shift(other.shift), sys(other.sys)
  { 

  }

  KeyboardButton::KeyboardButton(const sf::Event::KeyEvent& ke,
                                 Trigger::ButtonTrigger _trigger,
                                 bool _considering)
    : code(ke.code), trigger(_trigger), considering(_considering), 
      ctrl(ke.control), alt(ke.alt), shift(ke.shift), sys(ke.system)
  {
  }

  KeyboardButton::~KeyboardButton()
  {
  }

  bool KeyboardButton::operator==(const sf::Event& event) const
  {
    std::cerr << "testing equality between keyboardButton & Event" << std::endl;
    if (event.type != sf::Event::KeyPressed)
      {
        return operator==( KeyboardButton(event.key, 
                                          Trigger::PRESSED, 
                                          considering) );
      }
    if (event.type != sf::Event::KeyReleased)
      {
        return operator==( KeyboardButton(event.key, 
                                          Trigger::RELEASED, 
                                          considering) );
      }
    return operator==( KeyboardButton(event.key, 
                                      Trigger::CONTINUOUS, 
                                      considering) );
  }

  bool KeyboardButton::operator!=(const sf::Event& event) const
  {
    return not ( (*this) == event);
  }

  bool KeyboardButton::operator==(const KeyboardButton& other) const
  {
    std::cerr << "testing equality between keyboardButton & another" << std::endl;
    std::cerr << "code : " << code << "-" << other.code \
              << "trigger : " << trigger << "-" << other.trigger \
              << "considering : "<< considering <<"-"<<other.considering \
              << "ctrl : " << ctrl << "-" << other.ctrl \
              << "alt : " << alt <<"-"<< other.alt \
              << "shift : " << shift << "-" << other.shift \
              << "sys : "<< sys << "-" << other.sys << std::endl;

    return ( code == other.code 
             and trigger == other.trigger
             and (not considering 
                  or (
                      ctrl == other.ctrl
                      and alt == other.alt
                      and shift == other.shift
                      and sys == other.sys )
                  )
             );
  }

  bool KeyboardButton::operator!=(const KeyboardButton& other) const
  {
    return ( not operator==(other) );
  }

}
