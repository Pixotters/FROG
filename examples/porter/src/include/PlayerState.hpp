#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <functional>
#include <string>

class PlayerStateFactory;

class PlayerState
{
  typedef enum
    {
      STAND, 
      WALK, 
      JUMP, 
      FALLING, 
      CRAWLING,
      GETTING_UP,
      BUTTON,
      PUSHING, 
      PULLING, 
      WAITING,
      WINNING,
      HANDING,
      COUNT
    } ID;

  friend class PlayerStateFactory;

protected:
  std::function<bool()> m_enter;
  std::function<bool()> m_exit;
  ID m_id;

public:
  PlayerState(ID = "NORMAL");
  virtual ~PlayerState();
  virtual bool onEnter(); // should be abstract
  virtual bool onExit(); // should be abstract
  std::string getId() const;
};

#endif
