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

#ifndef FROG_JOYSTICKMOVER_HPP
#define FROG_JOYSTICKMOVER_HPP

#include "FROG/Core/Component.hpp"
#include <SFML/Window/Joystick.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{

  class JoystickMover : virtual public Component
  {

  public:
    typedef std::shared_ptr<JoystickMover> PTR;

  private:
    int up_velocity;
    int down_velocity;
    int left_velocity;
    int right_velocity;
    int joystick_id;
    unsigned short deadzone;
    sf::Joystick::Axis x;
    sf::Joystick::Axis y;

  public:
    JoystickMover(int up, int down, int left, int right, 
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned int joystickId = 0,
                  unsigned short deadzone = 25);
    JoystickMover(int velocity,
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned int joystickId = 0,
                  unsigned short deadzone = 25);
    virtual ~JoystickMover();
    sf::Vector2f getMovement() const;
    virtual void update(const ComponentHolder&); 
    static PTR create(int up, int down, int left, int right, 
                      sf::Joystick::Axis x,
                      sf::Joystick::Axis y,
                      unsigned int joystickId = 0,
                      unsigned short deadzone = 25);
    static PTR create(int velocity,
                      sf::Joystick::Axis x,
                      sf::Joystick::Axis y,
                      unsigned int joystickId = 0,
                      unsigned short deadzone = 25
                      );
  };

}
#endif
