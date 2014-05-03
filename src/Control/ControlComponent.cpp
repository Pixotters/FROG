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


  void ControlComponent::preupdate(const ComponentHolder& parent)
  {
    m_previousMouse = sf::Mouse::getPosition();
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
  
  sf::Vector2i ControlComponent::getMousePosition()
  {
    return sf::Mouse::getPosition();
  }

  sf::Vector2i ControlComponent::getMouseDelta()
  {
    return sf::Mouse::getPosition() - m_previousMouse;
  }

  sf::Vector2i ControlComponent::getMousePosition(const sf::Window& w)
  {
    return sf::Mouse::getPosition(w);
  }
 
  sf::Vector2i ControlComponent::getMouseDelta(const sf::Window& w)
  {
    return sf::Mouse::getPosition(w) - (m_previousMouse + w.getPosition() );
  }

}
