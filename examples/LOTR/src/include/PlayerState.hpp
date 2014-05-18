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
  typedef std::function<void()> FUN;

private:
  FUN onEnter;
  FUN onUpdate;
  FUN onExit;

public:
  PlayerState(FUN enter  = [](){},
              FUN update = [](){},
              FUN exit   = [](){} );
  PlayerState(const PlayerState&);
  virtual ~PlayerState();
  virtual void enter();
  virtual void update();
  virtual void exit();
  static PTR create(FUN = [](){},
                    FUN = [](){},
                    FUN = [](){} );

};

#endif
