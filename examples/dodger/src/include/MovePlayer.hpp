#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "Command.hpp"
#include "Player.hpp"

using namespace frog;

class MovePlayer : virtual public Command
{
  //// attributes ////
protected:
  Player * m_player;
  short m_x;
  short m_y;

  //// operations ////
public:
  MovePlayer(Player *, const short & = 0, const short& = 0);
  virtual ~MovePlayer();
  virtual bool execute();
};

#endif
