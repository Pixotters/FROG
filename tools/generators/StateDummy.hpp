#ifndef DUMMY_HPP
#define DUMMY_HPP

#include "State.hpp"

#include <SFML/Graphics.hpp>

class Dummy : virtual public State
{

  //// attributes ////
protected:

  //// operations ////
public:
  Dummy();

  virtual ~Dummy();

  // update the scene
  virtual void update();

  // draws the scene
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

};


#endif
