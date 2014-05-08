#include "FROG/App.hpp"
#include "FROG/Random.hpp"
#include "FROG/State.hpp"

namespace frog{

  App::App(const std::string& title, const std::string& cfg)
    : m_window(sf::VideoMode(1, 1), title, sf::Style::Close),
      appInfo(m_window, m_clock)
  {
    m_config.loadFromFile(cfg);
    m_window.create(sf::VideoMode(m_config.getWindowWidth(), 
                                  m_config.getWindowHeight() ), 
                    title, sf::Style::Close);
    // TODO center the window
    m_window.setPosition(sf::Vector2i(0,0) );
    m_window.setKeyRepeatEnabled(false);
  }

  App::~App()
  {
  }

  void App::init(State * startstate)
  {
    Random::init();
    if(startstate != nullptr)
      {
        m_stateManager.push( startstate );
      }
    appInfo.running = true;
  }

  void App::loop()
  {
    sf::Clock t0; // clock for counting delta-time
    while(appInfo.running)
      {
        if( m_window.isOpen() )
          {
            sf::Event event;
            appInfo.eventList.clear();
            while( m_window.pollEvent(event) )
              {
                if (event.type == sf::Event::Closed)
                  {
                    appInfo.running = false;
                    return;
                  } else
                  {
                    appInfo.eventList.push_back(event);
                  }
              }
          }
        appInfo.deltaTime = t0.restart().asSeconds(); 
        m_window.clear();
        m_stateManager.loop(appInfo);
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
  
}
