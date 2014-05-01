#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/MouseButton.hpp"

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
        if ( (*event) == e )
          {
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


}
