#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : virtual public Entity{

  //// attributes ////
protected:
  unsigned short m_lifes;
  unsigned long m_score;
  sf::Shape * m_boundingBox;

  //// operations ////
public:
  Player(const unsigned short& = 3);
  virtual ~Player();
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
  void setLifes(const unsigned short&);
  void addLife(const unsigned short& = 1);
  void removeLife(const unsigned short& = 1);
  void setScore(const unsigned long&);
  void addScore(const unsigned long& = 1);
  void removeScore(const unsigned long& = 1);

};

#endif
