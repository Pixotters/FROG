#ifndef FROG_ANYKEYBOARDBUTTON_HPP
#define FROG_ANYKEYBOARDBUTTON_HPP

#include "FROG/Control/Input.hpp"
#include "FROG/Control/ButtonTrigger.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  class AnyJoystickButton : virtual public Input
  {

  public:
    typedef std::shared_ptr<AnyJoystickButton> PTR;

  protected:
    Trigger::ButtonTrigger trigger;

  public:    
    AnyJoystickButton(Trigger::ButtonTrigger = Trigger::PRESSED);
    virtual ~AnyJoystickButton();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    static PTR create(Trigger::ButtonTrigger = Trigger::PRESSED);

  };

}

#endif
