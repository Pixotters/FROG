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

#include "FROG/Control/MouseButton.hpp"

namespace frog{

  MouseButton::MouseButton(sf::Mouse::Button _code,
                           Trigger::ButtonTrigger _trigger)
    : code(_code), trigger(_trigger)
  {

  }

  MouseButton::MouseButton(const MouseButton& other)
    : code(other.code), trigger(other.trigger)
  {

  }

  MouseButton::MouseButton(const sf::Event::MouseButtonEvent& event, 
                           Trigger::ButtonTrigger _trigger)
    : code(event.button), trigger(_trigger)
  {

  }

  MouseButton::~MouseButton()
  {

  }


  MouseButton::PTR MouseButton::create(sf::Mouse::Button code,
                                       Trigger::ButtonTrigger trigger)
  {
    return PTR( new MouseButton(code, trigger) );
  }

  MouseButton::PTR MouseButton::create(const sf::Event::MouseButtonEvent& e, 
                                       Trigger::ButtonTrigger trigger)
  {
    return PTR( new MouseButton(e, trigger) );
  }

  bool MouseButton::operator==(const sf::Event& event) const
  {
    if (trigger == Trigger::PRESSED
        && event.type != sf::Event::MouseButtonPressed)
      {
        return false;
      }
    
    if (trigger == Trigger::RELEASED
        && event.type != sf::Event::MouseButtonReleased)
      {
        return false;
      }
    
    return operator==(event.mouseButton);
  }

  bool MouseButton::operator!=(const sf::Event& event) const
  {
    return not ( (*this) == event);
  }
 
  bool MouseButton::operator==(const sf::Event::MouseButtonEvent& event) const
  {
    return code == event.button;
  }

  bool MouseButton::operator!=(const sf::Event::MouseButtonEvent& event) const
  {
    return code != event.button;
  }

  bool MouseButton::operator==(const MouseButton& other) const
  {
    return (code == other.code
            and trigger == other.trigger);
  }

  bool MouseButton::operator!=(const MouseButton& other) const
  {
    return (code != other.code
            or trigger != other.trigger);
    
  }

}
