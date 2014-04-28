#ifndef PLAYER_MACHINE_HPP
#define PLAYER_MACHINE_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"

#include "Level.hpp"
#include "FSM.hpp"
#include "PlayerState.hpp"

class PlayerMachine : virtual public frog::Component,
                      virtual public FSM<PlayerState>
{

protected:
  Level * m_level;

public:
  PlayerMachine(Level *);
  virtual ~PlayerMachine();
  void update(const frog::ComponentHolder&);

};

#endif
