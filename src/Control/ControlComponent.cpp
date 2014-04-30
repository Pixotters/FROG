#include "FROG/Control/ControlComponent.hpp"

#include <iostream>

namespace frog{

  ControlComponent::ControlComponent(const std::vector<sf::Event>& eventlist)
    : InputComponent(), m_eventList(eventlist)
  {

  }

  ControlComponent::~ControlComponent()
  {
  }

  bool ControlComponent::check(sf::Event * event, 
                               const ComponentHolder& p) const
  {
    std::cerr << "testing " << event << std::endl;
    return check(*event, p);
  }

  bool ControlComponent::check(const sf::Event& event, 
                               const ComponentHolder& parent) const
  {
    std::cerr << "has to test equality with " << m_eventList.size() << std::endl;
    for (auto e: m_eventList)
      {
        std::cerr << "checking equality" << std::endl;
        if ( equals(event, e) )
          {
            std::cerr << "input occured" << std::endl;
            return true;
          }
      }
    return false;
  }

  bool ControlComponent::equals(const sf::Event& e1, 
                                const sf::Event& e2) const
  {
    if (e1.type != e2.type)
      {
        return false;
      }else
      {
        switch (e1.type)
          {

          case sf::Event::Resized:
            return equals(e1.size, e2.size);
            break;

          case sf::Event::KeyPressed:
            return equals(e1.key, e2.key);
            break;
            
          case sf::Event::KeyReleased:
            return equals(e1.key, e2.key);
            break;

          case sf::Event::TextEntered:
            return equals(e1.text, e2.text);
            break;

          case sf::Event::MouseMoved:
            return equals(e1.mouseMove, e2.mouseMove);
            break;

          case sf::Event::MouseButtonPressed:
            return equals(e1.mouseButton, e2.mouseButton);
            break;

          case sf::Event::MouseButtonReleased:
            return equals(e1.mouseButton, e2.mouseButton);
            break;

          case sf::Event::MouseWheelMoved:
            return equals(e1.mouseWheel, e2.mouseWheel);
            break;

          case sf::Event::JoystickMoved:
            return equals(e1.joystickMove, e2.joystickMove);
            break;

          case sf::Event::JoystickButtonPressed:
            return equals(e1.joystickButton, e2.joystickButton);
            break;

          case sf::Event::JoystickButtonReleased:
            return equals(e1.joystickButton, e2.joystickButton);
            break;

          case sf::Event::JoystickConnected:
            return equals(e1.joystickConnect, e2.joystickConnect);
            break;

          case sf::Event::JoystickDisconnected:
            return equals(e1.joystickConnect, e2.joystickConnect);
            break;

          default: // Closed, LostFocus, GainFocus, MouseEntered, MouseLeft
            return true;
          }
      }
  }

  bool ControlComponent::equals(const sf::Event::SizeEvent& e1, 
                                const sf::Event::SizeEvent& e2) const
  {
    //    return (e1.width == e2.width and e1.height == e2.height);
    return true;
  }

  bool ControlComponent::equals(const sf::Event::KeyEvent& e1, 
                                const sf::Event::KeyEvent& e2) const
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

  bool ControlComponent::equals(const sf::Event::TextEvent& e1, 
                                const sf::Event::TextEvent& e2) const
  {
    return (e1.unicode == e2.unicode);
  }

  bool ControlComponent::equals(const sf::Event::MouseMoveEvent& e1, 
                                const sf::Event::MouseMoveEvent& e2) const
  {
    //    return (e1.x == e2.x and e1.y == e2.y);
    return true;
  }

  bool ControlComponent::equals(const sf::Event::MouseButtonEvent& e1, 
                                const sf::Event::MouseButtonEvent& e2) const
  {
    //    return (e1.button == e2.button and e1.x == e2.x and e1.y == e2.y);
    return (e1.button == e2.button);
  }

  bool ControlComponent::equals(const sf::Event::MouseWheelEvent& e1, 
                                const sf::Event::MouseWheelEvent& e2) const
  {
    //    return (e1.delta == e2.delta and e1.x == e2.x and e1.y == e2.y);
    return true;
  }

  bool ControlComponent::equals(const sf::Event::JoystickMoveEvent& e1, 
                                const sf::Event::JoystickMoveEvent& e2) const
  {
    /*    return (e1.joystickId == e2.joystickId 
            and e1.axis == e2.axis 
            and e1.position == e2.position); */
    return (e1.joystickId == e2.joystickId);
  }

  bool ControlComponent::equals(const sf::Event::JoystickButtonEvent& e1, 
                                const sf::Event::JoystickButtonEvent& e2) const
  {
    return (e1.joystickId == e2.joystickId
            and e1.button == e2.button);
  }

  bool ControlComponent::equals(const sf::Event::JoystickConnectEvent& e1, 
                                const sf::Event::JoystickConnectEvent& e2) const
  {
    return (e1.joystickId == e2.joystickId);
  }




}
