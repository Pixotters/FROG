#ifndef APP_HPP
#define APP_HPP

#include "Config.hpp"
#include "Scene.hpp" //delete
#include "State.hpp"
#include "Singleton.hpp"
//#include "InputManager.hpp"

#include <SFML/Window.hpp>

class App : virtual public Singleton<App>{

  friend class Singleton<App>;

  //// attributes ////
private:
  sf::RenderWindow m_window;
  Config m_config;
  sf::Clock m_clock;
  bool m_isRunning;
  const float m_fps = 60.0f;
  State * m_state; // replace by StateManager

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
  void init();
  void run();
  void exit();
  void handleEvents();
  void update(const sf::Time& dt);
  void render();
  bool isRunning()     const{  return m_isRunning;  };
  sf::Clock getClock() const{  return m_clock;      };
  Config getConfig()   const{  return m_config;     };

};

#endif
