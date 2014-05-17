#include "PlayerState.hpp"

using namespace frog;

PlayerState::PlayerState(std::shared_ptr<PlayerMachine>& ma,
                         GameObject::PTR o,
                         PlayerState::FUN enter, 
                         PlayerState::FUN update,
                         PlayerState::FUN exit)
  : State(),
    machine(ma),
    object(o),
    onEnter(enter), 
    onUpdate(update),
    onExit(exit)
{
  
}

PlayerState::~PlayerState()
{
}

void PlayerState::enter()
{
  onEnter(machine, object);
}

void PlayerState::update()
{
  onUpdate(machine, object);
}

void PlayerState::exit()
{
  onExit(machine, object);
}

PlayerState::PTR PlayerState::create(PlayerMachine::PTR ma,
                                     frog::GameObject::PTR ob,
                                     PlayerState::FUN enter, 
                                     PlayerState::FUN update,
                                     PlayerState::FUN exit)
{
  return PTR( new PlayerState(ma, ob, enter, update, exit) );
}

