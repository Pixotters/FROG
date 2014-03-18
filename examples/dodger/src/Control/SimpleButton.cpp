#include "Control/SimpleButton.hpp"

namespace ctrl{

  SimpleButton::SimpleButton(const SimpleButton::Trigger& t)
    : Button(), m_trigger(t)
  {

  }

  SimpleButton::~SimpleButton()
  {

  }

  SimpleButton::Trigger SimpleButton::getTrigger() const
  {
    return m_trigger;
  }


}
