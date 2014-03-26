#ifndef JOYSTICKMOVE_HPP
#define JOYSTICKMOVE_HPP

#include "Main/Command.hpp"
#include "Main/GameObject.hpp"
#include "Control/ControlHandler.hpp"


using namespace frog;

class JoystickMove : virtual public Command{

  //// attributes ////
private:
  unsigned int m_id;
  ctrl::ControlHandler * const m_controller;
  GameObject * const m_gameobject;

  //// operations ////
public:
  JoystickMove(GameObject * const,
               ctrl::ControlHandler * const,
               const unsigned int& = 0);
  virtual ~JoystickMove();
  virtual bool execute();

};


#endif
