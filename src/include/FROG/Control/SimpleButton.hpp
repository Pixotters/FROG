#ifndef FROG_CTRL_SIMPLEBUTTON_HPP
#define FROG_CTRL_SIMPLEBUTTON_HPP

#include "FROG/Control/Button.hpp"

namespace frog{

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

}

#endif
