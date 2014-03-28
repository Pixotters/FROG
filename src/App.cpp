#include "App.hpp"
#include "Random.hpp"


#include "State.hpp"

#include <iostream> // TODO remove

namespace frog{

  void App::init(State * startstate)
  {
    m_window = new sf::RenderWindow(sf::VideoMode(
                                                  m_config.getWindowWidth(), 
                                                  m_config.getWindowHeight() ),
                                    m_config.getTitle(), 
                                    sf::Style::Close);
    m_window->setPosition(sf::Vector2i(0,0) );
    m_window->setKeyRepeatEnabled(false);
    m_stateManager.push(startstate );
    m_isRunning = true;
  }

  void App::run()
  {
    sf::Clock t0; // clock for counting frame time
    float frameTime = 1.0f / m_fps;
    while(m_isRunning)
      {
        m_deltaTime = t0.restart();
        std::cerr << "updating..." <<std::endl;
        update();
        std::cerr << "rendering..." <<std::endl;
        render();        
        std::cerr << "rendered..." <<std::endl;
      }
  }

  void App::exit()
  {
    m_window->clear();
    m_window->close();
    State * s = m_stateManager.pop();
    delete s;
    delete m_window;
  }


  void App::update()
  {
    m_stateManager.update();
  }

  void App::render()
  {
    m_window->clear();
    m_stateManager.render(*m_window);
    m_window->display();
  }

}

