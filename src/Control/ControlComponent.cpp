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

#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/MouseButton.hpp"
#include "FROG/Control/JoystickButton.hpp"

namespace frog{

  sf::Vector2i ControlComponent::m_previousMouse(0, 0);

  ControlComponent::ControlComponent(const std::vector<sf::Event>& eventlist)
    : InputComponent(), m_eventList(eventlist)
  {
  }

  ControlComponent::~ControlComponent()
  {
  }


  void ControlComponent::preupdate(const ComponentHolder&)
  {
    m_previousMouse = sf::Mouse::getPosition();
  }

  bool ControlComponent::check(Input::PTR event, 
                               const ComponentHolder&) const
  {
    KeyboardButton::PTR kb;
    if ( (kb = std::dynamic_pointer_cast<KeyboardButton>(event) )
         and kb->trigger == Trigger::CONTINUOUS)
      {
        return isKeyboardPressed(kb->code);
      }
    MouseButton::PTR mb;
    if ( (mb = std::dynamic_pointer_cast<MouseButton>(event) ) 
         and mb->trigger == Trigger::CONTINUOUS)
      {
        return isMousePressed(mb->code);
      }
    JoystickButton::PTR jb;
    if ( (jb = std::dynamic_pointer_cast<JoystickButton>(event) ) 
         and jb->trigger == Trigger::CONTINUOUS)
      {
        return isJoystickPressed(jb->code, jb->id);
      }

    for (auto e: m_eventList)
      {
        if ( (*event) == e )
          {
            return true;
          }
      }
    return false;
  }
  
  bool ControlComponent::isKeyboardPressed(sf::Keyboard::Key k)
  {
    return (sf::Keyboard::isKeyPressed(k) );
  }
  
  bool ControlComponent::isMousePressed(sf::Mouse::Button b)
  {
    return (sf::Mouse::isButtonPressed(b) );
  }
 
  bool ControlComponent::isJoystickPressed(unsigned int button,
                                           unsigned int id)
  {
    return (sf::Joystick::isButtonPressed(button, id) );
  }
  
  sf::Vector2i ControlComponent::getMousePosition()
  {
    return sf::Mouse::getPosition();
  }

  sf::Vector2i ControlComponent::getMouseDelta()
  {
    return sf::Mouse::getPosition() - m_previousMouse;
  }

  sf::Vector2i ControlComponent::getMousePosition(const sf::Window& w)
  {
    return sf::Mouse::getPosition(w);
  }
 
  sf::Vector2i ControlComponent::getMouseDelta(const sf::Window& w)
  {
    return sf::Mouse::getPosition(w) - (m_previousMouse + w.getPosition() );
  }

  float ControlComponent::getJoystickAxis(sf::Joystick::Axis axis, 
                                          unsigned int id)
  {
    return sf::Joystick::getAxisPosition(id, axis);
  }

  sf::Vector2f ControlComponent::getJoystickPosition(unsigned int id)
  {
    sf::Vector2f res;
    res.x = sf::Joystick::getAxisPosition(id, sf::Joystick::X);
    res.y = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);
    return res;
  }

  sf::Vector2f ControlComponent::getJoystickPositionBis(unsigned int id)
  {
    sf::Vector2f res;
    res.x = sf::Joystick::getAxisPosition(id, sf::Joystick::Z);
    res.y = sf::Joystick::getAxisPosition(id, sf::Joystick::R);
    return res;
  }

  sf::Vector2f ControlComponent::getJoystickPositionTer(unsigned int id)
  {
    sf::Vector2f res;
    res.x = sf::Joystick::getAxisPosition(id, sf::Joystick::U);
    res.y = sf::Joystick::getAxisPosition(id, sf::Joystick::V);
    return res;
  }

  sf::Vector2f ControlComponent::getJoystickPOV(unsigned int id)
  {
    sf::Vector2f res;
    res.x = sf::Joystick::getAxisPosition(id, sf::Joystick::PovX);
    res.y = sf::Joystick::getAxisPosition(id, sf::Joystick::PovY);
    return res;
  }

  ControlComponent::PTR ControlComponent::create(const std::vector<sf::Event>& e)
  {
    return PTR(new ControlComponent(e) );
  }

}
