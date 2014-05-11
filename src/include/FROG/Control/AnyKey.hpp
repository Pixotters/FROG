#ifndef FROG_ANYKEY_HPP
#define FROG_ANYKEY_HPP

#include "FROG/Control/Input.hpp"
#include "FROG/Control/ButtonTrigger.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  class AnyKey : virtual public Input
  {

  public:
    typedef std::shared_ptr<AnyKey> PTR;

  protected:
    Trigger::ButtonTrigger trigger;

  public:    
    AnyKey(Trigger::ButtonTrigger = Trigger::PRESSED);
    virtual ~AnyKey();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    static PTR create(Trigger::ButtonTrigger = Trigger::PRESSED);

  };

}

#endif
