#include "FROG/App.hpp"
#include "FROG/Random.hpp"


#include "FROG/State.hpp"

#include <iostream> // TODO remove

namespace frog{

  App::App(const std::string& cfg)
  {
    m_config.loadFromFile(cfg);
    m_window.create(sf::VideoMode(
                                  m_config.getWindowWidth(), 
                                  m_config.getWindowHeight() ),
                    m_config.getTitle(), 
                    sf::Style::Close);
    // TODO center the window
    m_window.setPosition(sf::Vector2i(0,0) );
    m_window.setKeyRepeatEnabled(false);
    m_appInfo = new AppInfo(m_window, m_clock);
  }

  App::~App()
  {
  }

  void App::init(State * startstate)
  {
    if(startstate != nullptr){
      m_stateManager.push( startstate );
    }
    m_appInfo->running = true;
  }

  void App::loop()
  {
    sf::Clock t0; // clock for counting delta-time
    while(m_appInfo->running)
      {
        m_appInfo->deltaTime = t0.restart(); 
        m_window.clear();
        m_stateManager.loop(*m_appInfo);
        m_window.display();
      }
  }

  void App::exit()
  {
    m_window.clear();
    m_window.close();
  }

  Config App::getConfig() const
  { 
    return m_config; 
  }

  StateManager App::getStateManager() const
  {
    return m_stateManager; 
  }

  StateManager& App::getStateManager()
  {
    return m_stateManager; 
  }
  
  AppInfo& App::getAppInfo() const{
    return *m_appInfo;
  }

}
