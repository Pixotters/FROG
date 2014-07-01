/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#include "FROG/Core/App.hpp"
#include "FROG/Core/Random.hpp"
#include "FROG/Core/State.hpp"

namespace frog{

  App::App(const std::string& title, const std::string& cfg)
    : m_window(sf::VideoMode(1, 1), title, sf::Style::Close),
      appInfo(m_stateManager, m_window, m_clock)
  {
    config.loadFromFile(cfg);
    m_window.create(sf::VideoMode(config.windowSize.x, 
                                  config.windowSize.y ), 
                    title, 
                    config.windowStyle);
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
        appInfo.deltaTime = t0.restart(); 
        m_window.clear();
        if ( m_stateManager.isEmpty() )
          {
            appInfo.running = false;
            exit();
            break;
          }else{
          m_stateManager.update();
        }
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

}
