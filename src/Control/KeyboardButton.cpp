/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#include "FROG/Control/KeyboardButton.hpp"

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

  KeyboardButton::PTR KeyboardButton::create(sf::Keyboard::Key _code, 
                                             Trigger::ButtonTrigger _trigger, 
                                             bool _considering,
                                             bool _ctrl, 
                                             bool _alt, 
                                             bool _shift, 
                                             bool _sys)
  {
    return PTR( new KeyboardButton(_code, _trigger, _considering,
                                   _ctrl, _alt, _shift, _sys) );
  }

  KeyboardButton::PTR KeyboardButton::create(const KeyboardButton& kb)
  {
    return PTR( new KeyboardButton(kb) );

  }

  KeyboardButton::PTR KeyboardButton::create(const sf::Event::KeyEvent& ke, 
                                             Trigger::ButtonTrigger _trigger, 
                                             bool _considering)
  {
    return PTR( new KeyboardButton(ke, _trigger, _considering) );
  }

  bool KeyboardButton::operator==(const sf::Event& event) const
  {
    if (event.type == sf::Event::KeyPressed)
      {
        return operator==( KeyboardButton(event.key, 
                                          Trigger::PRESSED, 
                                          considering) );
      }
    if (event.type == sf::Event::KeyReleased)
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
