#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <functional>
#include <string>

class PlayerStateFactory;

class PlayerState
{

  friend class PlayerStateFactory;

protected:
  std::function<bool()> m_enter;
  std::function<bool()> m_exit;
  std::string m_id;

public:
  PlayerState(const std::string& = "");
  virtual ~PlayerState();
  virtual bool onEnter(); // should be abstract
  virtual bool onExit(); // should be abstract
  std::string getId() const;
};

#endif
