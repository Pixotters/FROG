#include "PlayerMachine.hpp"

using namespace frog;

PlayerMachine::PlayerMachine(PlayerState * _default)
  : Component(),
    FSM<PlayerState>(),
    defaultState(_default)
{
  if (_default != nullptr)
    push(defaultState);
}

PlayerMachine::PlayerMachine(const PlayerState::PTR& _default)
  : Component(),
    FSM<PlayerState>(),
    defaultState( _default.get() )
{
  push( _default.get() );
}

PlayerMachine::~PlayerMachine()
{
}

void PlayerMachine::setDefaultState(PlayerState * _default)
{
  defaultState = _default;
  if ( isEmpty() )
    {
      push(_default);
    }
}

void PlayerMachine::setDefaultState(const PlayerState::PTR& _default)
{
  setDefaultState( _default.get() );
}

void PlayerMachine::update(const ComponentHolder&)
{
  if (not isEmpty() )
    {
      auto time = clock.getElapsedTime();
      auto topState = top();
      // if lifetime of the state 
      if (time >= topState.getLifetime() )
        {
          restartClock();
          PlayerState * next = topState.getNext();
          if (next != nullptr)
            {
              next->resetCommands();
              auto nextPTR = PlayerState::create(*next);
              change( nextPTR );
            }else
            {
              defaultState->resetCommands();
              change(defaultState);
            }
        }
      // the current state is still relevant
      else
        {
          topState.update();
          // checking for commands
          auto commands = topState.getCommands();
          for (auto& pair : commands)
            {
              // the command has not been executed yet
              if (not pair.second)
                {
                  auto& subpair = pair.first;
                  // it is time to execute the command
                  if (time >= subpair.first)
                    {
                      subpair.second->execute();
                      // do not re-execute the command
                      pair.second = true;
                    }
                }
            }
          // endfor
        }
    }
  
}

void PlayerMachine::restartClock()
{
  clock.restart();
}

PlayerMachine::PTR PlayerMachine::create(PlayerState * defaultState)
{
  return PTR( new PlayerMachine(defaultState) );
}

PlayerMachine::PTR PlayerMachine::create(const PlayerState::PTR& defaultState)
{
  return PTR( new PlayerMachine(defaultState) );
}
