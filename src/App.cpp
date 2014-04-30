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
    delete m_appInfo;
  }

  void App::init(State * startstate)
  {
    Random::init();
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
        if( m_window.isOpen() )
          {
            sf::Event event;
            m_appInfo->eventList.clear();
            while( m_window.pollEvent(event) )
              {
                if (event.type == sf::Event::Closed)
                  {
                    m_appInfo->running = false;
                    return;
                  } else
                  {
                    std::cerr << "input occured : pushing - "<< m_appInfo->eventList.size() << std::endl;
                    m_appInfo->eventList.push_back(event);
                  }
              }
          }
        m_appInfo->deltaTime = t0.restart().asSeconds(); 
        m_window.clear();
        m_stateManager.loop(*m_appInfo);
        m_window.display();
      }
  }

  void App::exit()
  {
    m_window.clear();
    m_window.close();
    m_stateManager.clear();
  }

  void App::start(State * s)
  {
    init(s);
    loop();
    exit();
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
