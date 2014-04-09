#ifndef FROG_APP_HPP
#define FROG_APP_HPP

#include "FROG/Config.hpp"
#include "FROG/Control/ControlHandler.hpp"
#include "FROG/StateManager.hpp"
#include "FROG/State.hpp"
#include "FROG/Singleton.hpp"

#include <SFML/Window.hpp>

/*!
 * Namespace of all FROG-related stuff
 */
namespace frog{

  /*!
   * App class is the main control class of FROG, providing essential features
   * like diverting the flow, loading global configuration...
   */
  // TODO : remove singleton
  class App : virtual public Singleton<App>
  { 

    friend class Singleton<App>;

    //// attributes ////
  private:
    /// The current window where the app runs
    sf::RenderWindow * m_window;

    /// The config, loaded from a file
    Config m_config;

    /// The program clock, starts when App is created
    sf::Clock m_clock;

    /// Time elapsed since last frame
    sf::Time m_deltaTime;

    /// Tells if the game is running, making the game loop or not
    bool m_isRunning;

    /// The desired FPS
    const float m_fps = 60.0f;

    /// State flow stack : top state will be used for updating and rendering
    StateManager m_stateManager;

    //// operations ////
  private:

    /*! 
     * @brief Default constructor. 
     * @details Also loads the config file.
     */
    App();

    /*!
     * @brief Destructor
     * @details Also calls destroy function. 
     */
    virtual ~App();

  public:

    /*!
     * @brief Initializes the game engine at the given state. 
     * @details Processes prelude code that may be required before starting the 
     loop. The given state will be the entry state. 
     * @param s initial state
     */
    void init(State * s);
  
    /*!
     * @brief Starts the game loop
     * @details The game loop will update current state and render it. 
     */
    void run();
  
    /*!
     * @brief Shuts down the engine. 
     * @details Before closing, users may have to process different kind of 
     * things such as freeing memory. 
    */
    void exit();
  
    /*!
     * @brief Updates the current state. 
     * @details The updated state is the top state of the state manager. 
     */
    void update();
  
    /*!
     * @brief Renders the current state. 
     * @details The rendered state is the top state of the state manager. 
     */
    void render();
  
    /*!
     * @brief Tells if the game is running. 
     */
    bool isRunning() const;

    /*!
     * @brief Returns the sf::RenderWindow of the program. 
     * @details The sf::RenderWindow can be required for some infos. 
     * @return Pointer to the global rendering area. 
     */
    sf::RenderWindow * getWindow() const;
  
    /*!
     * @brief Returns the time elapsed since engine has been launched. 
     * @return Clock started at the beginning of the program. 
     */
    sf::Clock getClock() const;
  
    /*!
     * @brief Returns delta time.
     * @details Delta time is the time elapsed since last frame. 
     * @return An sf::Time containing the delta time.
     */
    sf::Time getDeltaTime() const;
  
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

  };

}

#endif
