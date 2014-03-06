#include "Controller.hpp"

#include "App.hpp"

#include <iostream>

Controller::Controller()
{
  sf::Event e;
  e.type = sf::Event::KeyPressed;
  e.key.code = sf::Keyboard::A;
  suscribeOneTime(sf::Keyboard::A, new Action("LEFT") );
  sf::Event e2;
  e2.type = sf::Event::KeyPressed;
  e2.key.code = sf::Keyboard::E;
  suscribeOneTime(e2.key.code, new Action("RIGHT") );
  suscribeRealTime(sf::Keyboard::D, new Action("RIGHT") );
  suscribeRealTime(sf::Keyboard::Q, new Action("LEFT") );
}

Controller::~Controller()
{

}

void Controller::handleInputs(sf::Window * w)
{
  while(not m_actions.empty() )
    {
      m_actions.pop();
    }
  handleOneTime(w);
  handleRealTime();
}

void Controller::handleRealTime()
{
  sf::Keyboard::Key k = sf::Keyboard::A;
  for(int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
      
      sf::Keyboard::Key k = static_cast<sf::Keyboard::Key>(i);
    
      if(sf::Keyboard::isKeyPressed(k) )
        {
          auto action = m_binding.find(k);
          if(action != m_binding.end() )
            std::cout << "real-time action : "                  \
                      << action->second->getName() << std::endl;
          m_actions.push( action->second );
        }
    }
}

void Controller::handleOneTime(sf::Window * w)
{
  sf::Event event;
  while( w -> pollEvent(event)  )
    {
      if( event.type ==  sf::Event::Closed )
        {
          App::instance()->exit();
        }else if( event.type == sf::Event::KeyPressed){
        auto action = m_binding.find(event.key.code);
        if(action != m_binding.end() )
          std::cout << "one-time action : "\
                    << action->second->getName() << std::endl;
        m_actions.push( action->second );
      }
    
    }


}

void Controller::suscribeOneTime(const sf::Keyboard::Key& k, Action * a)
{
  m_binding.insert(std::pair<sf::Keyboard::Key, Action *>(k, a) );
}

void Controller::suscribeRealTime(const sf::Keyboard::Key& k, Action * a)
{
  m_binding.insert(std::pair<sf::Keyboard::Key, Action *>(k, a) );
}

void Controller::unsuscribeOneTime()
{

}

void Controller::unsuscribeRealTime()
{

}

std::queue<Action *> Controller::getActions()
{
  return m_actions;
}
