#ifndef FROG_INPUT_HPP
#define FROG_INPUT_HPP

#include <SFML/Window/Event.hpp>

namespace frog{

  /*!
   * Input is an abstract class representing an event that can occur thanks 
   * to user devices such as Keyboard, Mouse, and Joystick. 
   */
  struct Input
  {
    virtual bool operator==(const sf::Event&) const = 0;
    virtual bool operator!=(const sf::Event&) const = 0;
  };

}

#endif
