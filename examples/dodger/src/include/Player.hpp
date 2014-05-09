#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "FROG/GameObject.hpp"

#include "FROG/Transform.hpp"

#include <SFML/Graphics/Shape.hpp>


using namespace frog;

class Player : public GameObject
{

  //// attributes ////
public:
  unsigned short lives;
  unsigned long score;
  unsigned char row;
  unsigned short multiplier;

  //// operations ////
public:
  /**
     the parameter 'l' is the initial number of lives a new player has
  */
  Player(const unsigned short & l = 3);

  virtual ~Player();


};

#endif
