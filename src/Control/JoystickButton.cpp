#include "FROG/Control/JoystickButton.hpp"

namespace frog{

  JoystickButton::JoystickButton(unsigned int _code,
                                 Trigger::ButtonTrigger _trigger,
                                 unsigned int _id)
    : id(_id), code(_code), trigger(_trigger)
  {

  }

  JoystickButton::JoystickButton(const JoystickButton& other)
    : id(other.id), code(other.code), trigger(other.trigger)
  {

  }

  JoystickButton::JoystickButton(const JoystickButton& other,
                                 unsigned int _id)
    : id(_id), code(other.code), trigger(other.trigger)
  {

  }

  JoystickButton::JoystickButton(const sf::Event::JoystickButtonEvent& event, 
                                 Trigger::ButtonTrigger _trigger)
    : id(event.joystickId), code(event.button), trigger(_trigger)
  {

  }

  JoystickButton::~JoystickButton()
  {

  }

  JoystickButton::PTR_JoystickButton JoystickButton::create(unsigned int _code, 
                                                            Trigger::ButtonTrigger _trigger,
                                                            unsigned int _id)
  {
    return PTR_JoystickButton(new JoystickButton(_code, _trigger, _id) );
  }

  JoystickButton::PTR_JoystickButton JoystickButton::create(const sf::Event::JoystickButtonEvent& event,
                                                            Trigger::ButtonTrigger _trigger)
  {
    return PTR_JoystickButton(new JoystickButton(event, _trigger) );
  }

  bool JoystickButton::operator==(const sf::Event& event) const
  {
    if (trigger == Trigger::PRESSED
        && event.type != sf::Event::JoystickButtonPressed)
      {
        return false;
      }
    
    if (trigger == Trigger::RELEASED
        && event.type != sf::Event::JoystickButtonReleased)
      {
        return false;
      }
    
    return operator==(event.joystickButton);
  }

  bool JoystickButton::operator!=(const sf::Event& event) const
  {
    return not ( (*this) == event);
  }

  bool JoystickButton::operator==(const sf::Event::JoystickButtonEvent& event) const
  {
    return (code == event.button and id == event.joystickId);
  }

  bool JoystickButton::operator!=(const sf::Event::JoystickButtonEvent& event) const
  {
    return (code != event.button or id != event.joystickId);
  }
  
  bool JoystickButton::operator==(const JoystickButton& other) const
  {
    return (id == other.id
            and code == other.code
            and trigger == other.trigger);
  }

  bool JoystickButton::operator!=(const JoystickButton& other) const
  {
    return (id != other.id
            or code != other.code
            or trigger != other.trigger);
    
  }

}
