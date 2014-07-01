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

#include "FROG/Control/AnyMouseButton.hpp"

namespace frog{

  AnyMouseButton::AnyMouseButton(Trigger::ButtonTrigger tr)
    : Input(), trigger(tr)
  {
    
  }

  AnyMouseButton::~AnyMouseButton()
  {
  }

  bool AnyMouseButton::operator==(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type == sf::Event::MouseButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type == sf::Event::MouseButtonReleased;
    return false;
  }

  bool AnyMouseButton::operator!=(const sf::Event& e) const
  {
    if (trigger == Trigger::PRESSED or trigger == Trigger::CONTINUOUS)
      return e.type != sf::Event::MouseButtonPressed;
    if (trigger == Trigger::RELEASED)
      return e.type != sf::Event::MouseButtonReleased;
    return true;
  }

  AnyMouseButton::PTR AnyMouseButton::create(Trigger::ButtonTrigger tr)
  {
    return (AnyMouseButton::PTR(new AnyMouseButton(tr) ) );
  }

}
