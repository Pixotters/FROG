#ifndef SIMPLEBUTTON_HPP
#define SIMPLEBUTTON_HPP

#include "Button.hpp"

namespace Input{

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
