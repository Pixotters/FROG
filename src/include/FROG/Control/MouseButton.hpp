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

#ifndef FROG_MOUSEBUTTON_HPP
#define FROG_MOUSEBUTTON_HPP

#include "FROG/Control/ButtonTrigger.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  struct MouseButton : virtual public Input
  {

    typedef std::shared_ptr<MouseButton> PTR;

    sf::Mouse::Button code;
    Trigger::ButtonTrigger trigger;

    MouseButton(sf::Mouse::Button code,
                Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    MouseButton(const MouseButton&);
    MouseButton(const sf::Event::MouseButtonEvent&, 
                Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    virtual ~MouseButton();
    static PTR create(sf::Mouse::Button code,
                      Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    static PTR create(const sf::Event::MouseButtonEvent& e, 
                      Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    virtual bool operator==(const sf::Event::MouseButtonEvent&) const;
    virtual bool operator!=(const sf::Event::MouseButtonEvent&) const;
    bool operator==(const MouseButton&) const;
    bool operator!=(const MouseButton&) const;

  };

}

#endif
