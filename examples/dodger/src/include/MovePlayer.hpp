#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Command.hpp"

using namespace frog;

class MovePlayer : virtual public Command
{
  //// attributes ////
protected:
  GameObject * m_player;
  short m_x;
  short m_y;
  const AppInfo& m_appInfo;

  //// operations ////
public:
  MovePlayer(GameObject *, const short &, const short&, const AppInfo& );
  virtual ~MovePlayer();
  virtual void execute();
};

#endif
