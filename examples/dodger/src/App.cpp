#include "App.hpp"
#include "Random.hpp"

#include <iostream> // TODO remove

#include "StartState.hpp"

void App::init()
{
  m_window = new sf::RenderWindow(sf::VideoMode(
                                                m_config.getWindowWidth(), 
                                                m_config.getWindowHeight() ),
                                  m_config.getTitle(), 
                                  sf::Style::Close);
  m_window->setPosition(sf::Vector2i(0,0) );
  m_window->setKeyRepeatEnabled(false);
  m_controller = new ctrl::Controller(m_window);
    m_stateManager.push(new StartState() );
  //  m_stateManager.push(new XboxTest() );
  m_isRunning = true;
}

void App::run()
{
  sf::Clock t0; // clock for counting frame time
  float frameTime = 1.0f / m_fps;
  while(m_isRunning)
    {
      m_deltaTime = t0.restart();
      m_controller->handle();
      handleCommands();
      update();
      render();
    }
}

void App::exit()
{
  m_window->clear();
  m_window->close();
  State * s = m_stateManager.pop();
  delete s;
  delete m_window;
  delete m_controller;
}

void App::handleCommands()
{
  m_stateManager.handleCommands( m_controller );
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


//////////////////////////////////////:


int main(){
  std::cout << "Starting game" << std::endl;
  App::instance()->init();
  Random::init();
  std::cout << "Initialization successful. Running..." << std::endl;
  App::instance()->run();
  std::cout << "Stopping game..." << std::endl;
  App::instance()->exit();
  std::cout << "Ended game properly" << std::endl;

}
