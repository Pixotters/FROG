#include "App.hpp"

void App::init()
{
  m_window.create(sf::VideoMode(
                                  m_config.getWindowWidth(), 
                                  m_config.getWindowHeight() ),
                    m_config.getTitle(), 
                    sf::Style::Close);
  m_state = new Scene;
  m_isRunning = true;
}

void App::run()
{
  sf::Clock t0; // time elapsed since the last looping
  sf::Time t1 = sf::Time::Zero; // time elapsed since the last frame
  float frameTime = 1.0f / m_fps;
  while(m_isRunning)
    {
      /**      handleEvents();
      t1 += t0.restart(); 
      // it is possible that a frame could take a very long time to render
      while( t1 > (frameTime) ) 
        {
          t1 -= frameTime;
          handleEvents();
          update(frameTime);
        }
      */
      sf::Time dt = t0.restart();
      handleEvents();
      update(dt);
      render();
    }
}

void App::exit()
{
  m_window.close();
}

void App::handleEvents()
{
  /*  sf::Event event
    while(m_window.pollEvent(event) )
      {
        if(event.type == sf::Event::Closed)
          {
            exit();
          }
        Action::Type action = m_config.getAction(event);
        if(action != Action::None){
          state->addAction(action);
        }
        }*/
}

void App::update(const sf::Time& dt)
{
  m_state->update(dt);
}

void App::render()
{
  m_window.clear();
  m_state->draw(m_window, sf::RenderStates::Default);
  m_window.display();
}


//////////////////////////////////////:


int main(){
  App::instance()->init();
  App::instance()->run();
  App::instance()->exit();

}
