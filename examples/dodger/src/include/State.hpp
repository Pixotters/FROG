#ifndef STATE_HPP
#define STATE_HPP

#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

class State : virtual public sf::Drawable{

  //// attributes ////
protected : 
  Renderer * m_renderer;

  //// operations ////
public :
  State();
  virtual ~State();

  /*
    computes the state's logic. 
   */
  virtual void update(const sf::Time& dt) = 0;

  /*
    render the state
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

};

#endif
