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

#ifndef FROG_XBOX_HPP
#define FROG_XBOX_HPP

#include <SFML/Window/Event.hpp>

/*!
 * Provides facilities for handling XBOX360 controller. 
 * XBOX::Button gives the buttons, XBOX::Axis gives the joysticks. 
 */
namespace XBOX{

  typedef enum{
    A = 0,
    B = 1,
    X = 2,
    Y = 3,
    LB = 4,
    RB = 5,
    BACK = 6,
    START = 7,
    HOME = 8,
    LS = 9,
    RS = 10
  } Button;

  // axis : top-left is (-100,-100). bottom-right is (100,100)
  typedef enum{
    LSTICK_X = sf::Joystick::X,
    LSTICK_Y = sf::Joystick::Y,
    RSTICK_X = sf::Joystick::U,
    RSTICK_Y = sf::Joystick::V,
    POV_X = sf::Joystick::PovX,
    POV_Y = sf::Joystick::PovY
  } Axis;

}

#endif
