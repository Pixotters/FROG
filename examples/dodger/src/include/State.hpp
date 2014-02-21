#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class State : virtual sf::Drawable{

  //// attributes ////
protected : 

  //// operations ////
public :
  State();
  virtual ~State();
  virtual void update(const sf::Time& dt) = 0;
  virtual void draw(sf::RenderTarget&, 
                    sf::RenderStates = sf::RenderStates::Default) const = 0;

};

#endif
