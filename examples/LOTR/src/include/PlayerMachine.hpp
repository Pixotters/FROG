#ifndef PLAYERMACHINE_HPP
#define PLAYERMACHINE_HPP


#include <FROG/Core/FSM.hpp>
#include <FROG/Core/Component.hpp>

class PlayerState;

class PlayerMachine : virtual public frog::FSM<PlayerState>,
                      virtual public frog::Component
{

public:
  typedef std::shared_ptr<PlayerMachine> PTR;

public:
  unsigned short frame; // current frame, to sync with animations

public:
  PlayerMachine();
  virtual ~PlayerMachine();
  void resetCount();
  virtual void update(const frog::ComponentHolder&);

};

#endif
