#ifndef FROG_ANYKEY_HPP
#define FROG_ANYKEY_HPP

#include "FROG/Control/Input.hpp"
#include "FROG/Control/ButtonTrigger.hpp"

#include <SFML/Window/Event.hpp>

#include <memory>

namespace frog{

  class AnyKey : virtual public Input
  {

  protected:
    Trigger::ButtonTrigger trigger;

  public:
    typedef std::shared_ptr<AnyKey> PTR_AnyKey;
    
    AnyKey(Trigger::ButtonTrigger = Trigger::PRESSED);
    virtual ~AnyKey();
    virtual bool operator==(const sf::Event&) const;
    virtual bool operator!=(const sf::Event&) const;
    static PTR_AnyKey create(Trigger::ButtonTrigger = Trigger::PRESSED);

  };

}

#endif
