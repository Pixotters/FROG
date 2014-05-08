#ifndef FROG_STATE_HPP
#define FROG_STATE_HPP

#include "FROG/Rendering/Renderer.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace frog{

  /*!
   * A State is a point of the program. They are used by the State Manager. 
   */
  class State{

    friend class StateManager;

    //// attributes ////
  protected : 

    /// Default renderer of the state
    Renderer * m_renderer;

    //// operations ////
  public :

    State();

    virtual ~State();

    /*!
     * @brief Updates and renders the state
     * @param appinfo AppInfo containing at least the RenderTarget and delta-time
     */
    void loop(sf::RenderTarget&);

  protected:

    /*!
     * @brief function performed when StateManager enters in this scene
     */
    virtual void enter() = 0;

    /*!
     * @brief Updates the state. 
     */
    virtual void update() = 0;

    /*!
     * @brief function performed when StateManager exits from the scene
     */
    virtual void exit() = 0;

    /*!
     * @brief Renders the state in the given RenderTarget. 
     * @param rt Where to display the state. 
     */
    void render(sf::RenderTarget& rt) const;

  };

}

#endif
