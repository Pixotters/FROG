#ifndef INPUT_BUTTON_HPP
#define INPUT_BUTTON_HPP

#include "Input.hpp"
#include <SFML/Window/Event.hpp>

namespace Input{

  class Button : virtual public Input
  {

  public :
    typedef enum{
      PRESSED,
      RELEASED,
      CONTINUOUS
    } Trigger;

    //// attributes ////
  protected:
    Trigger m_trigger;

    //// operations ////
  public:
    Button(const Trigger&);
    virtual ~Button();
    Trigger getTrigger() const;
    virtual bool isContinuous() const;
  };

}


#endif
