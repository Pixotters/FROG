#ifndef DUMMY_HPP
#define DUMMY_HPP

#include "GameObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Dummy : virtual public GameObject
{

  //// attributes ////
protected:

  //// operations ////
public:

  Dummy();

  virtual ~Dummy();

  /*
    Renders the Dummy. Must call `rt.draw(drawable, rs)` where drawable 
    is the appearence of the Dummy
   */
  virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;

  /*
    Optionnal code, adds behaviour
   */
  virtual void update();


};

#endif
