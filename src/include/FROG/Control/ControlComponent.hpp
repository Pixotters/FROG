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
  };

}

#endif
