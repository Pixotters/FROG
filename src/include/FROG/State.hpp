#ifndef FROG_STATE_HPP
#define FROG_STATE_HPP

#include "FROG/Rendering/Renderer.hpp"

#include "FROG/AppInfo.hpp"
#include "FROG/Command.hpp"

#include <SFML/Graphics.hpp>
#include <list>


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
    void loop(const AppInfo& appinfo);

  protected:
    /*!
     * @brief Updates the state. 
     * @param appinfo AppInfo containing at least a good delta-time
     */
    virtual void update(const AppInfo& appinfo) = 0;

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
