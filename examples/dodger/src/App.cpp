#include "App.hpp"

#include <iostream> // delete

void App::init()
{
  m_window = new sf::RenderWindow(sf::VideoMode(
                                                m_config.getWindowWidth(), 
                                                m_config.getWindowHeight() ),
                                  m_config.getTitle(), 
                                  sf::Style::Close);
  m_state = new Scene;
  m_isRunning = true;
}

void App::run()
{
  sf::Clock t0; // clock for counting frame time
  float frameTime = 1.0f / m_fps;
  while(m_isRunning)
    {
      m_deltaTime = t0.restart();
      handleEvents();
      update();
      render();
    }
}

void App::exit()
{
  m_window->close();
  delete m_window;
}

void App::handleEvents()
{
  sf::Event event;
  while(m_window->pollEvent(event) )
    {
      if(event.type == sf::Event::Closed)
        {
          m_isRunning = false;
        }
      /*Action::Type action = m_config.getAction(event);
        if(action != Action::None){
        state->addAction(action);
        }*/
    }
}

void App::update()
{
  m_state->update();
}

void App::render()
{
  m_window->clear();
  m_state->draw(*m_window, sf::RenderStates::Default);
  m_window->display();
}


//////////////////////////////////////:


int main(){
  std::cout << "Starting game" << std::endl;
  App::instance()->init();
  App::instance()->run();
  App::instance()->exit();
  std::cout << "Ended game properly" << std::endl;

}
