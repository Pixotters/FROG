#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP

#include <FROG/Core/State.hpp>
#include <FROG/Core/GameObject.hpp>

#include <functional>
#include <memory>

#include "PlayerMachine.hpp"

class PlayerState : virtual public frog::State
{

public:
  typedef std::shared_ptr<PlayerState> PTR;
  typedef std::function<void(PlayerMachine::PTR&, frog::GameObject::PTR)> FUN;

private:
  FUN onEnter;
  FUN onUpdate;
  FUN onExit;
public:
  PlayerMachine::PTR machine;
  frog::GameObject::PTR object;

public:
  PlayerState(std::shared_ptr<PlayerMachine>& machine,
              frog::GameObject::PTR o,
              FUN enter
              = [](PlayerMachine::PTR, frog::GameObject::PTR){},
              FUN update
              = [](PlayerMachine::PTR, frog::GameObject::PTR){},
              FUN exit
              = [](PlayerMachine::PTR, frog::GameObject::PTR){} );
  virtual ~PlayerState();
  virtual void enter();
  virtual void update();
  virtual void exit();
  static PTR create(PlayerMachine::PTR machine,
                    frog::GameObject::PTR o,
                    FUN
                    = [](PlayerMachine::PTR, frog::GameObject::PTR){},
                    FUN
                    = [](PlayerMachine::PTR, frog::GameObject::PTR){},
                    FUN
                    = [](PlayerMachine::PTR, frog::GameObject::PTR){} );

};

#endif
