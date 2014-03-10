#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics.hpp>

class StartState : virtual public State
{

  //// attributes ////
protected:

  //// operations ////
public:
  StartState();

  virtual ~StartState();

  virtual void update();

  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  virtual void handleCommands(Controller *);

};


#endif
