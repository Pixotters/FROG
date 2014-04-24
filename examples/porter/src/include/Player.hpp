#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "FROG/GameObject.hpp"

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
    WINNING
  } Player_State;

class Player : virtual public GameObject
{

public:
  
  Player();

  virtual ~Player();

};

#endif
