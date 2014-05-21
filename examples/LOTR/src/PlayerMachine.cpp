#include "PlayerMachine.hpp"

#include <iostream> // TODO remove

using namespace frog;

PlayerMachine::PlayerMachine(PlayerStateFactory _factory)
  : Component(),
    FSM<PlayerState>(),
    factory(_factory)
{
  defaultState = factory.get(PlayerState::STAND);
  push( defaultState );
}

PlayerMachine::~PlayerMachine()
{
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
              std::cout << "changing for pointed " << next << std::endl;
              change( nextPTR );
              std::cout << "changed" << std::endl;
            }else
            {
              defaultState->resetCommands();
              std::cout << "changing for default " << defaultState->getID() << std::endl;
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

PlayerState::PTR PlayerMachine::get(PlayerState::ID id)
{
  return factory.get(id);
}

void PlayerMachine::restartClock()
{
  clock.restart();
}

PlayerMachine::PTR PlayerMachine::create(PlayerStateFactory factory)
{
  return PTR( new PlayerMachine(factory) );
}
