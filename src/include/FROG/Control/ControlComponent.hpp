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

#ifndef FROG_CONTROLCOMPONENT_HPP
#define FROG_CONTROLCOMPONENT_HPP

#include "FROG/Control/InputComponent.hpp"
#include "FROG/Control/Command.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Window.hpp>

#include <memory>
#include <vector>

namespace frog{

  class ControlComponent : virtual public InputComponent<Input, Command>
  {

  public:
    typedef std::shared_ptr<ControlComponent> PTR;

  protected:
    static sf::Vector2i m_previousMouse;
    const std::vector<sf::Event>& m_eventList;

  public:
    ControlComponent(const std::vector<sf::Event>& );
    virtual ~ControlComponent();
    virtual void preupdate(const ComponentHolder&);
    virtual bool check(std::shared_ptr<Input>, const ComponentHolder&) const;
    static bool isKeyboardPressed(sf::Keyboard::Key);
    static bool isMousePressed(sf::Mouse::Button);
    static bool isJoystickPressed(unsigned int button, 
                                  unsigned int id = 0);
    static sf::Vector2i getMousePosition();
    static sf::Vector2i getMouseDelta();
    static sf::Vector2i getMousePosition(const sf::Window&);
    static sf::Vector2i getMouseDelta(const sf::Window&);
    static float getJoystickAxis(sf::Joystick::Axis, 
                                 unsigned int id = 0);
    static sf::Vector2f getJoystickPosition(unsigned int id = 0);
    static sf::Vector2f getJoystickPositionBis(unsigned int id = 0);
    static sf::Vector2f getJoystickPositionTer(unsigned int id = 0);
    static sf::Vector2f getJoystickPOV(unsigned int id = 0);
    static PTR create(const std::vector<sf::Event>&);
    
  };

}

#endif
