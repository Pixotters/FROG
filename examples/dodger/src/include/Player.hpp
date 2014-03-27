#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Main/GameObject.hpp"

#include "Main/Transform.hpp"

#include "SAPList.hpp"


using namespace frog;

class Player : virtual public GameObject,
               virtual public Collisionable
{

  //// attributes ////
protected:
  unsigned short m_lives;
  unsigned long m_score;
  sf::Shape * m_boundingBox;

  //// operations ////
public:
  /**
     the parameter 'l' is the initial number of lives a new player has
  */
  Player(const unsigned short & l = 3);

  virtual ~Player();

  /*
    updates the player : currently, just changing its positions to the mouse's 
    position
  */
  virtual void update();

  /*
    draws the player : just its bounding box, created in the constructor to
    save instructions. only the position changes.
  */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

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

  int getXMin() const{
    return m_transform.getPosition().x+m_boundingBox->getLocalBounds().left;
  }

  int getXMax() const{
    sf::FloatRect fr = m_boundingBox->getLocalBounds();
    return m_transform.getPosition().x+fr.left+ fr.width;
  }

  int getYMin() const{
    return m_transform.getPosition().y+m_boundingBox->getLocalBounds().top;

  }

  int getYMax() const{
    sf::FloatRect fr = m_boundingBox->getLocalBounds();
    return m_transform.getPosition().y+fr.top+fr.height;
  }


  };

#endif
