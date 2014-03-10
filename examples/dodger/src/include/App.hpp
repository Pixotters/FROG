#ifndef APP_HPP
#define APP_HPP

#include "Config.hpp"
#include "Controller.hpp"
#include "StateManager.hpp"
#include "Singleton.hpp"

#include <SFML/Window.hpp>

class App : virtual public Singleton<App>{

  friend class Singleton<App>;

  //// attributes ////
private:
  // the current window where the app runs
  sf::RenderWindow * m_window;

  // the config, loaded from a file
  Config m_config;

  // the program clock, can be useful
  sf::Clock m_clock;

  // time elapsed since last frame
  sf::Time m_deltaTime;

  // tells if the game is running (if we make loop)
  bool m_isRunning;

  // the desired FPS
  const float m_fps = 60.0f;

  // the current state, must be replaced by a stateManager
  StateManager m_stateManager;

  // filters the inputs and translates them into commands //
  Controller * m_controller;

  //// operations ////
private:
  App()
  {
    m_config.loadFromFile("config.cfg");
  }
  virtual ~App()
  {
    destroy();
  }

public:
  /*
    process prelude code that may be required before starting the loop
   */
  void init();
  
  /*
    make a looping : handle events, compute logic, render
   */
  void run();
  
  /*
    before closing, we may have to process thing (free memory allocated in init)
   */
  void exit();
  
  /*
    make the current state handle events
   */
  void handleCommands();
  
  /*
    updates the current state
   */
  void update();
  
  /*
    renders the current state
   */
  void render();
  
  /*
    tells if the game is running
   */
  bool isRunning() const{ return m_isRunning;  };

  /*
    returns the window, useful for drawing the renderer here.
   */
  sf::RenderWindow * getWindow() const{ return m_window; };
  
  /*
    returns the clock
   */
  sf::Clock getClock() const{ return m_clock; };
  
  /*
    returns the delta time : time elapsed since last frame
   */
  sf::Time getDeltaTime() const{ return m_deltaTime; };
  
  /*
    returns the config
   */
  Config getConfig() const{ return m_config; };

  /*
    returns the state handler
  */
  StateManager getStateManager() const{ return m_stateManager; };
  StateManager& getStateManager(){ return m_stateManager; };

  Controller * getController() { return m_controller; };

};

#endif
