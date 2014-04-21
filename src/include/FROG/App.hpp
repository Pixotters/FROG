#ifndef FROG_APP_HPP
#define FROG_APP_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/Config.hpp"
#include "FROG/StateManager.hpp"
#include "FROG/State.hpp"

#include <SFML/Window.hpp>

/*!
 * Namespace of all FROG-related stuff
 */
namespace frog{

  /*!
   * App class is the main control class of FROG, providing essential features
   * like diverting the flow, loading global configuration...
   */
  class App
  { 

    //// attributes ////
  protected:
    /// The current window where the app runs
    sf::RenderWindow m_window;

    /// The config, initially loaded from a file
    Config m_config;

    AppInfo * m_appInfo;

    /// The program clock, starts when App is created
    sf::Clock m_clock;

    /// State flow stack : top state will be used for updating and rendering
    StateManager m_stateManager;

    //// operations ////

  public:

    /*!
     * @brief Default constructor. 
     * @details Also loads the config file.
     * @param cfg config file to load. If not given, load "config.cfg"
     */
    App(const std::string& cfg = "config.cfg");

    /*!
     * @brief Destructor
     * @details Also calls destroy function. 
     */
    virtual ~App();

    /*!
     * @brief Initializes, loops, and exits properly the App
     * @details Calls init(s), loop(), and exit()
     * @param s State to initialize App with
     */
    void start(State * s = nullptr);
  
    /*!
     * @brief Returns current config. 
     * @return Current config. 
     */
    Config getConfig() const;

    /*!
     * @brief Returns copy of the current state manager. 
     * @return Copy of the current state manager. 
     */
    StateManager getStateManager() const;

    /*!
     * @brief Returns reference to current state manager. 
     * @return Reference to current state manager. 
     */
    StateManager& getStateManager();

    AppInfo& getAppInfo() const;

    /*!
     * @brief Initializes the game engine at the given state. 
     * @details Processes prelude code that may be required before starting the 
     loop. The given state will be the entry state. 
     * @param s initial state
     */
    void init(State * s = nullptr);
  
    /*!
     * @brief Starts the game loop
     * @details The game loop will update current state and render it. 
     */
    void loop();
  
    /*!
     * @brief Shuts down the engine. 
     * @details Before closing, users may have to process different kind of 
     * things such as freeing memory. 
    */
    void exit();

  };

}

#endif
