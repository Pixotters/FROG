#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <functional>

class PlayerStateFactory;

class PlayerState
{

  friend class PlayerStateFactory;

protected:
  std::function<bool()> m_enter;
  std::function<bool()> m_exit;

public:
  PlayerState();
  virtual ~PlayerState();
  virtual bool onEnter(); // should be abstract
  virtual bool onExit(); // should be abstract
};

#endif
