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
