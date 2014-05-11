#ifndef FROG_MOUSEBUTTON_HPP
#define FROG_MOUSEBUTTON_HPP

#include "FROG/Control/ButtonTrigger.hpp"
#include "FROG/Control/Input.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  struct MouseButton : virtual public Input
  {

    typedef std::shared_ptr<MouseButton> PTR;

    sf::Mouse::Button code;
    Trigger::ButtonTrigger trigger;

    MouseButton(sf::Mouse::Button code,
                Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    MouseButton(const MouseButton&);
    MouseButton(const sf::Event::MouseButtonEvent&, 
                Trigger::ButtonTrigger trigger = Trigger::CONTINUOUS);
    virtual ~MouseButton();
    static PTR create(sf::Mouse::Button code,
                                  Trigger::ButtonTrigger trigger);
    static PTR create(const sf::Event::MouseButtonEvent& e, 
                                  Trigger::ButtonTrigger trigger);
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    virtual bool operator==(const sf::Event::MouseButtonEvent&) const;
    virtual bool operator!=(const sf::Event::MouseButtonEvent&) const;
    bool operator==(const MouseButton&) const;
    bool operator!=(const MouseButton&) const;

  };

}

#endif
