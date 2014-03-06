#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "Action.hpp"
#include "Player.hpp"

class MovePlayer : virtual public Action
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
