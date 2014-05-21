#include "ChangeState.hpp"

#include <iostream> //TODO remove

ChangeState::ChangeState(PlayerMachine::PTR _machine, 
                         PlayerStateFactory::PTR _factory, 
                         PlayerState::ID _id)
  : Command(),
    machine(_machine),
    factory(_factory),
    id(_id)
{
}

ChangeState::~ChangeState()
{
}

void ChangeState::execute()
{
  machine->restartClock();
  std::cerr << "changing state to " << id << std::endl;
  std::cerr << "factory " << factory.get() << std::endl;
  auto state = factory->get(id);
  if (machine->isEmpty() )
    {
      machine->push(state);
    }else
    {
      machine->change(state);
    }
}

ChangeState::PTR ChangeState::create(PlayerMachine::PTR _machine, 
                                     PlayerStateFactory::PTR _factory, 
                                     PlayerState::ID _id)
{
  return PTR( new ChangeState(_machine, _factory, _id) );
}

