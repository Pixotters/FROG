#ifndef STATE_HPP
#define STATE_HPP

#include "Control/Controller.hpp"
#include "Control/ControlManager.hpp"
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
  virtual void update() = 0;

  /*
    render the state
   */
  virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

  void handleCommands(ctrl::Controller *, 
                      ControlManager<ctrl::Input, Command> *);
};

#endif
