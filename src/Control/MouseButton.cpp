#include "FROG/Control/MouseButton.hpp"

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


  MouseButton::PTR MouseButton::create(sf::Mouse::Button code,
                                Trigger::ButtonTrigger trigger)
  {
    return PTR( new MouseButton(code, trigger) );
  }

  MouseButton::PTR MouseButton::create(const sf::Event::MouseButtonEvent& e, 
                                Trigger::ButtonTrigger trigger)
  {
    return PTR( new MouseButton(e, trigger) );
  }

  bool MouseButton::operator==(const sf::Event& event) const
  {
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
    return (code == other.code
            and trigger == other.trigger);
  }

  bool MouseButton::operator!=(const MouseButton& other) const
  {
    return (code != other.code
            or trigger != other.trigger);
    
  }

}
