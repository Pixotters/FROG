#include "ChangeState.hpp"

ChangeState::ChangeState(PlayerMachine::PTR _machine, 
                         PlayerState::ID _id)
  : Command(),
    machine(_machine),
    id(_id)
{
}

ChangeState::~ChangeState()
{
}

void ChangeState::execute()
{
  machine->restartClock();
  auto state = machine->get(id);
  if (machine->isEmpty() )
    {
      machine->push(state);
    }else
    {
      machine->change(state);
    }
}

ChangeState::PTR ChangeState::create(PlayerMachine::PTR _machine, 
                                     PlayerState::ID _id)
{
  return PTR( new ChangeState(_machine, _id) );
}

