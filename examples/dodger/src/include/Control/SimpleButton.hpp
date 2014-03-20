#ifndef CTRL_SIMPLEBUTTON_HPP
#define CTRL_SIMPLEBUTTON_HPP

#include "Control/Button.hpp"

namespace ctrl{

  class SimpleButton : virtual public Button
  {
  public :
    typedef enum{
      PRESSED,
      RELEASED
    } Trigger;
    

    //// attributes ////
  protected:
    Trigger m_trigger;
    
    //// operations ////
  public:
    SimpleButton(const Trigger& = SimpleButton::PRESSED);
    virtual ~SimpleButton();
    Trigger getTrigger() const;
  };

}

#endif