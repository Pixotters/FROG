#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Element.hpp"

#include <SFML/Graphics.hpp>


using namespace frog;

class Enemy : virtual public Element
{

  //// attributes ////
protected:

  //// operations ////
public:
  Enemy();
  virtual ~Enemy();

};

#endif
