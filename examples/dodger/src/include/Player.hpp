#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "FROG/GameObject.hpp"

#include "FROG/Transform.hpp"

#include <SFML/Graphics/Shape.hpp>


using namespace frog;

class Player : public GameObject
{

  //// attributes ////
protected:
  unsigned short m_lives;
  unsigned long m_score;

  //// operations ////
public:
  /**
     the parameter 'l' is the initial number of lives a new player has
  */
  Player(const unsigned short & l = 3);

  virtual ~Player();

  /*
    returns the number of lives
  */
  unsigned short getLives() const;

  /*
    changes the number of lives
  */
  void setLives(const unsigned short&);

  /*
    add the given amount of lives (no check for the unsigned shorts' ceiling)
  */
  void addLives(const unsigned short& = 1);

  /*
    removes the given amount of lives, with a check for 0.
  */
  void removeLives(const unsigned short& = 1);

  /*
    returns the current score
  */
  unsigned long getScore() const;

  /*
    changes the current score
  */
  void setScore(const unsigned long&);

  /*
    add the given number to the score (no check for the unsigned shorts' ceiling)
  */
  void addScore(const unsigned long& = 1);

  /*
    removes the given number to the score, with a check for 0
  */
  void removeScore(const unsigned long& = 1);

  };

#endif
