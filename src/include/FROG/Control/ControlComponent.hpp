#ifndef FROG_CONTROLCOMPONENT_HPP
#define FROG_CONTROLCOMPONENT_HPP

#include "FROG/Control/InputComponent.hpp"
#include "FROG/ComponentHolder.hpp"
#include "FROG/Command.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <vector>

namespace frog{

  class ControlComponent : virtual public InputComponent<Input, Command>
  {

  protected:
    const std::vector<sf::Event>& m_eventList;

  public:
    ControlComponent(const std::vector<sf::Event>& );
    virtual ~ControlComponent();
    virtual bool check(Input *, const ComponentHolder&) const;
    static bool isKeyboardPressed(sf::Keyboard::Key);
    static bool isMousePressed(sf::Mouse::Button);
    /*
    virtual bool check(const sf::Event&, const ComponentHolder&) const;
    bool equals(const sf::Event&, const sf::Event&) const;
    bool equals(const sf::Event::SizeEvent&, 
                const sf::Event::SizeEvent&) const;
    bool equals(const sf::Event::KeyEvent&, 
                const sf::Event::KeyEvent&) const;
    bool equals(const sf::Event::TextEvent&, 
                const sf::Event::TextEvent&) const;
    bool equals(const sf::Event::MouseMoveEvent&, 
                const sf::Event::MouseMoveEvent&) const;
    bool equals(const sf::Event::MouseButtonEvent&, 
                const sf::Event::MouseButtonEvent&) const;
    bool equals(const sf::Event::MouseWheelEvent&, 
                const sf::Event::MouseWheelEvent&) const;
    bool equals(const sf::Event::JoystickMoveEvent&, 
                const sf::Event::JoystickMoveEvent&) const;
    bool equals(const sf::Event::JoystickButtonEvent&, 
                const sf::Event::JoystickButtonEvent&) const;
    bool equals(const sf::Event::Event::JoystickConnectEvent&, 
                const sf::Event::Event::JoystickConnectEvent&) const;
    */
  };

}

#endif
