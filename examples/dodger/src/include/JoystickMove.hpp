#ifndef JOYSTICKMOVE_HPP
#define JOYSTICKMOVE_HPP

#include "Command.hpp"
#include "GameObject.hpp"
#include "Control/Controller.hpp"

class JoystickMove : virtual public Command{

  //// attributes ////
private:
  unsigned int m_id;
  ctrl::Controller * const m_controller;
  GameObject * const m_gameobject;

  //// operations ////
public:
  JoystickMove(GameObject * const,
               ctrl::Controller * const,
               const unsigned int& = 0);
  virtual ~JoystickMove();
  virtual bool execute();

};


#endif
