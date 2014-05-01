#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/MouseButton.hpp"
#include <iostream>


namespace frog{

  ControlComponent::ControlComponent(const std::vector<sf::Event>& eventlist)
    : InputComponent(), m_eventList(eventlist)
  {
  }

  ControlComponent::~ControlComponent()
  {
  }

  bool ControlComponent::check(Input * event, 
                               const ComponentHolder& parent) const
  {
    std::cerr << "has to test equality with " << m_eventList.size() << std::endl;
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

    for (auto e: m_eventList)
      {
        std::cerr << "checking equality" << std::endl;
        if ( (*event) == e )
          {
            std::cerr << "input occured" << std::endl;
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


  /*
  bool ControlComponent::equals(const Input& e1, 
                                const Input& e2) const
  {
    if (e1.type != e2.type)
      {
        return false;
      }else
      {
        switch (e1.type)
          {

          case Input::Resized:
            return equals(e1.size, e2.size);
            break;

          case Input::KeyPressed:
            return equals(e1.key, e2.key);
            break;
            
          case Input::KeyReleased:
            return equals(e1.key, e2.key);
            break;

          case Input::TextEntered:
            return equals(e1.text, e2.text);
            break;

          case Input::MouseMoved:
            return equals(e1.mouseMove, e2.mouseMove);
            break;

          case Input::MouseButtonPressed:
            return equals(e1.mouseButton, e2.mouseButton);
            break;

          case Input::MouseButtonReleased:
            return equals(e1.mouseButton, e2.mouseButton);
            break;

          case Input::MouseWheelMoved:
            return equals(e1.mouseWheel, e2.mouseWheel);
            break;

          case Input::JoystickMoved:
            return equals(e1.joystickMove, e2.joystickMove);
            break;

          case Input::JoystickButtonPressed:
            return equals(e1.joystickButton, e2.joystickButton);
            break;

          case Input::JoystickButtonReleased:
            return equals(e1.joystickButton, e2.joystickButton);
            break;

          case Input::JoystickConnected:
            return equals(e1.joystickConnect, e2.joystickConnect);
            break;

          case Input::JoystickDisconnected:
            return equals(e1.joystickConnect, e2.joystickConnect);
            break;

          default: // Closed, LostFocus, GainFocus, MouseEntered, MouseLeft
            return true;
          }
      }
  }
  */

  /*
  bool ControlComponent::equals(const Input::SizeEvent& e1, 
                                const Input::SizeEvent& e2) const
  {
    //    return (e1.width == e2.width and e1.height == e2.height);
    return true;
  }

  bool ControlComponent::equals(const Input::KeyEvent& e1, 
                                const Input::KeyEvent& e2) const
  {
    std::cerr << "both are key events : " \
              << e1.code <<"=="<< e2.code << std::endl \
              << e1.control << "==" << e2.control<< std::endl \
              << e1.alt << "==" << e2.alt<< std::endl \
              << e1.shift << "==" << e1.shift<< std::endl \
              << e1.system << "==" << e2.system << std::endl;
    return (e1.code == e2.code 
            and e1.control == e2.control
            and e1.alt == e2.alt
            and e1.shift == e1.shift
            and e1.system == e2.system);
  }

  bool ControlComponent::equals(const Input::TextEvent& e1, 
                                const Input::TextEvent& e2) const
  {
    return (e1.unicode == e2.unicode);
  }

  bool ControlComponent::equals(const Input::MouseMoveEvent& e1, 
                                const Input::MouseMoveEvent& e2) const
  {
    //    return (e1.x == e2.x and e1.y == e2.y);
    return true;
  }

  bool ControlComponent::equals(const Input::MouseButtonEvent& e1, 
                                const Input::MouseButtonEvent& e2) const
  {
    //    return (e1.button == e2.button and e1.x == e2.x and e1.y == e2.y);
    return (e1.button == e2.button);
  }

  bool ControlComponent::equals(const Input::MouseWheelEvent& e1, 
                                const Input::MouseWheelEvent& e2) const
  {
    //    return (e1.delta == e2.delta and e1.x == e2.x and e1.y == e2.y);
    return true;
  }

  bool ControlComponent::equals(const Input::JoystickMoveEvent& e1, 
                                const Input::JoystickMoveEvent& e2) const
  {
    return (e1.joystickId == e2.joystickId);
  }

  bool ControlComponent::equals(const Input::JoystickButtonEvent& e1, 
                                const Input::JoystickButtonEvent& e2) const
  {
    return (e1.joystickId == e2.joystickId
            and e1.button == e2.button);
  }

  bool ControlComponent::equals(const Input::JoystickConnectEvent& e1, 
                                const Input::JoystickConnectEvent& e2) const
  {
    return (e1.joystickId == e2.joystickId);
  }
*/



}
