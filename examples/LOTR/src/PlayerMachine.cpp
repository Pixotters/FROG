#include "PlayerMachine.hpp"

using namespace frog;

PlayerMachine::PlayerMachine(PlayerState * _default)
  : Component(),
    FSM<PlayerState>(),
    defaultState(_default)
{

}

PlayerMachine::~PlayerMachine()
{
}

void PlayerMachine::setDefaultState(PlayerState * _defaultState)
{
  defaultState = _defaultState;
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
          PlayerState * next = topState.getNext();
          if (next != nullptr)
            {
              next->resetCommands();
              change( next );
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


PlayerMachine::PTR PlayerMachine::create(PlayerState * defaultState)
{
  return PTR( new PlayerMachine(defaultState) );
}
