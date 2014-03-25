#ifndef BOMB_HPP
#define BOMB_HPP

#include "Command.hpp"
#include "Enemy.hpp"

#include <list>


class Bomb : virtual public frog::Command
{
  //// operations ////
protected:
  std::list<Enemy *>& m_list;

  //// attributes ////
public:
  Bomb(std::list<Enemy *>&);
  virtual ~Bomb();
  virtual bool execute();

};

#endif
