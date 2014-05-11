#ifndef FROG_ANYMOUSEBUTTON_HPP
#define FROG_ANYMOUSEBUTTON_HPP

#include "FROG/Control/Input.hpp"
#include "FROG/Control/ButtonTrigger.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  class AnyMouseButton : virtual public Input
  {

  protected:
    Trigger::ButtonTrigger trigger;

  public:
    typedef std::shared_ptr<AnyMouseButton> PTR;
    
    AnyMouseButton(Trigger::ButtonTrigger = Trigger::PRESSED);
    virtual ~AnyMouseButton();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    static PTR create(Trigger::ButtonTrigger = Trigger::PRESSED);

  };

}

#endif
