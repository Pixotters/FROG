#ifndef FROG_ANYKEYBOARDBUTTON_HPP
#define FROG_ANYKEYBOARDBUTTON_HPP

#include "FROG/Control/Input.hpp"
#include "FROG/Control/ButtonTrigger.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  class AnyKeyboardButton : virtual public Input
  {

  protected:
    Trigger::ButtonTrigger trigger;

  public:
    typedef std::shared_ptr<AnyKeyboardButton> PTR;
    
    AnyKeyboardButton(Trigger::ButtonTrigger = Trigger::PRESSED);
    virtual ~AnyKeyboardButton();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    static PTR create(Trigger::ButtonTrigger = Trigger::PRESSED);

  };

}

#endif
