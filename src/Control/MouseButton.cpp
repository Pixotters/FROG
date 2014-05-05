#include "FROG/Control/MouseButton.hpp"

#include <iostream>

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

  bool MouseButton::operator==(const sf::Event& event) const
  {
    std::cerr << "testing equality between MouseButton & Event " << std::endl;

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
    std::cerr << "testing equality mousebutton & another: " << std::endl \
              << "code : " << code << " - " << other.code << std::endl \
              << "trigger : " << trigger << " - " <<other.trigger << std::endl;
    return (code == other.code
            and trigger == other.trigger);
  }

  bool MouseButton::operator!=(const MouseButton& other) const
  {
    return (code != other.code
            or trigger != other.trigger);
    
  }

}
