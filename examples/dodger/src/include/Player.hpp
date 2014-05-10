#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "FROG/GameObject.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

using namespace frog;

class Player : public GameObject
{

  //// attributes ////
public:
  unsigned short lives;
  unsigned long score;
  unsigned char row;
  unsigned short multiplier;
  bool invincible;
  sf::Time timer;

  //// operations ////
public:
  /**
     the parameter 'l' is the initial number of lives a new player has
  */
  Player(const unsigned short & l = 3);

  virtual ~Player();

  void hit();

  void checkTime();

private:
  void changeColor(const sf::Color&);

};

#endif
