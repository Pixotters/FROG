#ifndef STATE_HPP
#define STATE_HPP

#include "Rendering/Renderer.hpp"

#include "Command.hpp"

#include <SFML/Graphics.hpp>
#include <list>


namespace frog{

  class State{

    //// attributes ////
  protected : 
    render::Renderer * m_renderer;

    //// operations ////
  public :
    State();
    virtual ~State();

    /*
      computes the state's logic. 
    */
    virtual void update() = 0;

    void render(sf::RenderTarget& rt) const;

    void handleCommands(std::list<Command *>); 
  };

}

#endif
