#ifndef PLAYERMACHINE_HPP
#define PLAYERMACHINE_HPP

#include "PlayerState.hpp"
#include "PlayerStateFactory.hpp"

#include <FROG/Core/Component.hpp>
#include <FROG/Core/ComponentHolder.hpp>
#include <FROG/Core/FSM.hpp>

#include <SFML/System/Clock.hpp>

#include <memory>
#include <vector>

class PlayerMachine : virtual public frog::Component,
                      virtual public frog::FSM<PlayerState>
{

public:
  typedef std::shared_ptr<PlayerMachine> PTR;

private:
  sf::Clock clock;
  PlayerState::PTR defaultState;
  PlayerStateFactory factory;

public:
  PlayerMachine(PlayerStateFactory _factory);
  virtual ~PlayerMachine();
  void setDefaultState(PlayerState * defaultState);
  void setDefaultState(const PlayerState::PTR& defaultState);
  virtual void update(const frog::ComponentHolder&);
  static PTR create(PlayerStateFactory _factory);
  PlayerState::PTR get(PlayerState::ID);
  void restartClock();

};

#endif
