#include "PlayerMachine.hpp"

#include <iostream> // TODO remove

using namespace frog;

PlayerMachine::PlayerMachine(PlayerStateFactory _factory, 
                             PlayerState * _default)
  : Component(),
    FSM<PlayerState>(),
    defaultState(_default),
    factory(_factory)
{
  std::cout << "machine" << std::endl;
  if (_default != nullptr)
    push(defaultState);
}

PlayerMachine::PlayerMachine(PlayerStateFactory _factory, 
                             const PlayerState::PTR& _default)
  : Component(),
    FSM<PlayerState>(),
    defaultState( _default.get() ),
    factory(_factory)
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

PlayerState::PTR PlayerMachine::get(PlayerState::ID id)
{
  auto find = states.find(id);
  if (find != states.end() )
    {
      return find->second;
    }else
    {
      auto st = factory.createState(id);
      states.emplace(id, st);
      return st;
    }
}

void PlayerMachine::restartClock()
{
  clock.restart();
}

PlayerMachine::PTR PlayerMachine::create(PlayerStateFactory factory, 
                                         PlayerState * defaultState)
{
  return PTR( new PlayerMachine(factory, defaultState) );
}

PlayerMachine::PTR PlayerMachine::create(PlayerStateFactory factory, 
                                         const PlayerState::PTR& defaultState)
{
  return PTR( new PlayerMachine(factory, defaultState) );
}
