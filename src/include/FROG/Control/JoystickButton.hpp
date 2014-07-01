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

#ifndef FROG_JOYSTICKBUTTON_HPP
#define FROG_JOYSTICKBUTTON_HPP

#include "FROG/Control/ButtonTrigger.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>
#include <memory>

namespace frog{

  struct JoystickButton : virtual public Input
  {

    typedef std::shared_ptr<JoystickButton> PTR;

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
    static PTR create(unsigned int code, 
                      Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS,
                      unsigned int id = 0);
    static PTR create(const sf::Event::JoystickButtonEvent&,
                      Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    virtual bool operator==(const sf::Event::JoystickButtonEvent&) const;
    virtual bool operator!=(const sf::Event::JoystickButtonEvent&) const;
    bool operator==(const JoystickButton&) const;
    bool operator!=(const JoystickButton&) const;

  };

}
#endif
