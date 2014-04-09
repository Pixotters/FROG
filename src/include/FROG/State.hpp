#ifndef FROG_STATE_HPP
#define FROG_STATE_HPP

#include "FROG/Rendering/Renderer.hpp"

#include "FROG/Command.hpp"

#include <SFML/Graphics.hpp>
#include <list>


namespace frog{

  /*!
   * A State is a point of the program. They are used by the State Manager. 
   */
  class State{

    //// attributes ////
  protected : 

    /// Default renderer of the state
    render::Renderer * m_renderer;

    //// operations ////
  public :

    State();

    virtual ~State();

    /*!
     * @brief Updates the state. 
     */
    virtual void update() = 0;

    /*!
     * @brief Renders the state in the given RenderTarget. 
     * @param rt Where to display the state. 
     */
    void render(sf::RenderTarget& rt) const;

    /*!
     * @brief Handles a list of commands, by executing them in order.
     * @param c List of commands to execute. 
     */
    void handleCommands(std::list<Command *> c); 

  };

}

#endif
