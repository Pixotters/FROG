#ifndef CHANGESTATE_HPP
#define CHANGESTATE_HPP

#include "PlayerMachine.hpp"
#include "PlayerState.hpp"

#include <FROG/Control/Command.hpp>

#include <memory>

class ChangeState : virtual public frog::Command
{

public:
  typedef std::shared_ptr<ChangeState> PTR;

private:
  PlayerMachine::PTR machine;
  PlayerState::ID id;

public:
  ChangeState(PlayerMachine::PTR, PlayerState::ID);
  virtual ~ChangeState();
  virtual void execute();
  static PTR create(PlayerMachine::PTR, 
                    PlayerState::ID);
};

#endif
