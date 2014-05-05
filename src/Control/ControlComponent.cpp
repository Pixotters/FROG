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


  void ControlComponent::preupdate(const ComponentHolder& parent)
  {
    m_previousMouse = sf::Mouse::getPosition();
  }

  bool ControlComponent::check(Input * event, 
                               const ComponentHolder& parent) const
  {
    KeyboardButton * kb;
    if ( (kb = dynamic_cast<KeyboardButton *>(event) )
         and kb->trigger == Trigger::CONTINUOUS)
      {
        return isKeyboardPressed(kb->code);
      }
    MouseButton * mb;
    if ( (mb = dynamic_cast<MouseButton *>(event) ) 
         and mb->trigger == Trigger::CONTINUOUS)
      {
        return isMousePressed(mb->code);
      }
    JoystickButton * jb;
    if ( (jb = dynamic_cast<JoystickButton *>(event) ) 
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


}
