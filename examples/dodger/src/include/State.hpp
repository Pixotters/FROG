#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State : virtual public sf::Drawable{

  //// attributes ////
protected : 

  //// operations ////
public :
  State();
  virtual ~State();

  /*
    computes the state's logic. 
   */
  virtual void update(const sf::Time& dt) = 0;

  /*
    render's the state
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

};

#endif
