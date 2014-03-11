#include "Input/Button.hpp"

namespace Input{

  Button::Button(const Button::Trigger& t)
    : Input(), m_trigger(t)
  {

  }

  Button::~Button()
  {

  }

  Button::Trigger Button::getTrigger() const
  {
    return m_trigger;
  }

  bool Button::isContinuous() const{
    return (m_trigger == Button::CONTINUOUS);
  }

}
