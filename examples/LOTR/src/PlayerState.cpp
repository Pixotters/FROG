#include "PlayerState.hpp"

using namespace frog;

PlayerState::PlayerState(PlayerState::FUN enter, 
                         PlayerState::FUN update,
                         PlayerState::FUN exit)
  : State(),
    onEnter(enter), 
    onUpdate(update),
    onExit(exit)
{
  
}

PlayerState::PlayerState(const PlayerState& other)
  : State(),
    onEnter(other.onEnter),
    onUpdate(other.onUpdate),
    onExit(other.onExit)
{
}

PlayerState::~PlayerState()
{
}

void PlayerState::enter()
{
  onEnter();
}

void PlayerState::update()
{
  onUpdate();
}

void PlayerState::exit()
{
  onExit();
}

PlayerState::PTR PlayerState::create(PlayerState::FUN enter, 
                                     PlayerState::FUN update,
                                     PlayerState::FUN exit)
{
  return PTR( new PlayerState(enter, update, exit) );
}

