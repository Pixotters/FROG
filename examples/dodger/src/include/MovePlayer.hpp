#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/Command.hpp"
#include "Player.hpp"

using namespace frog;

class MovePlayer : virtual public Command
{
  //// attributes ////
protected:
  Player * m_player;
  short m_x;
  short m_y;
  const AppInfo& m_appInfo;

  //// operations ////
public:
  MovePlayer(Player *, const short &, const short&, const AppInfo& );
  virtual ~MovePlayer();
  virtual bool execute();
};

#endif
