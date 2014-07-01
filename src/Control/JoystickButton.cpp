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

#include "FROG/Control/JoystickButton.hpp"

namespace frog{

  JoystickButton::JoystickButton(unsigned int _code,
                                 Trigger::ButtonTrigger _trigger,
                                 unsigned int _id)
    : id(_id), code(_code), trigger(_trigger)
  {

  }

  JoystickButton::JoystickButton(const JoystickButton& other)
    : id(other.id), code(other.code), trigger(other.trigger)
  {

  }

  JoystickButton::JoystickButton(const JoystickButton& other,
                                 unsigned int _id)
    : id(_id), code(other.code), trigger(other.trigger)
  {

  }

  JoystickButton::JoystickButton(const sf::Event::JoystickButtonEvent& event, 
                                 Trigger::ButtonTrigger _trigger)
    : id(event.joystickId), code(event.button), trigger(_trigger)
  {

  }

  JoystickButton::~JoystickButton()
  {

  }

  JoystickButton::PTR JoystickButton::create(unsigned int _code, 
                                             Trigger::ButtonTrigger _trigger,
                                             unsigned int _id)
  {
    return PTR(new JoystickButton(_code, _trigger, _id) );
  }

  JoystickButton::PTR JoystickButton::create(const sf::Event::JoystickButtonEvent& event,
                                             Trigger::ButtonTrigger _trigger)
  {
    return PTR(new JoystickButton(event, _trigger) );
  }

  bool JoystickButton::operator==(const sf::Event& event) const
  {
    if (trigger == Trigger::PRESSED
        && event.type != sf::Event::JoystickButtonPressed)
      {
        return false;
      }
    
    if (trigger == Trigger::RELEASED
        && event.type != sf::Event::JoystickButtonReleased)
      {
        return false;
      }
    
    return operator==(event.joystickButton);
  }

  bool JoystickButton::operator!=(const sf::Event& event) const
  {
    return not ( (*this) == event);
  }

  bool JoystickButton::operator==(const sf::Event::JoystickButtonEvent& event) const
  {
    return (code == event.button and id == event.joystickId);
  }

  bool JoystickButton::operator!=(const sf::Event::JoystickButtonEvent& event) const
  {
    return (code != event.button or id != event.joystickId);
  }
  
  bool JoystickButton::operator==(const JoystickButton& other) const
  {
    return (id == other.id
            and code == other.code
            and trigger == other.trigger);
  }

  bool JoystickButton::operator!=(const JoystickButton& other) const
  {
    return (id != other.id
            or code != other.code
            or trigger != other.trigger);
    
  }

}
