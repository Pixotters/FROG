#include "ChangeState.hpp"

using namespace frog;

ChangeState::ChangeState(const PlayerStateFactory::PTR& _factory, 
                         const std::string& id)
  : Command(), 
    factory(_factory ),
    what(id)
{
}

ChangeState::ChangeState(const ChangeState& other)
  : Command(), what(other.what), factory(other.factory)
{
}

ChangeState::~ChangeState()
{
}

void ChangeState::execute()
{
  auto nextState = PlayerState::PTR( new PlayerState(factory->get(what)) );
  if (factory->machine->isEmpty() )
    {
      factory->machine->push(nextState);
    }else
    {
      factory->machine->change(nextState);
    }
}

std::shared_ptr<ChangeState> ChangeState::create(const PlayerStateFactory::PTR& m, 
                                                 const std::string& id)
{
  return std::shared_ptr<ChangeState>(new ChangeState(m, id) );
}


