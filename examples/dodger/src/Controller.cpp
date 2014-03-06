#include "Controller.hpp"

#include "App.hpp"

#include <iostream>

Controller::Controller()
{

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
          auto action = m_RTbinding.find(k);
          if(action != m_RTbinding.end() )
            {
              m_actions.push( action->second );
            }
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
        }else if( event.type == sf::Event::KeyReleased){
        auto action = m_OTbinding.find(event.key.code);
        if(action != m_OTbinding.end() ){         
          m_actions.push( action->second );
        }
      }
    
    }


}

void Controller::suscribeOneTime(const sf::Keyboard::Key& k, Action * a)
{
  m_OTbinding.insert(std::pair<sf::Keyboard::Key, Action *>(k, a) );
}

void Controller::suscribeRealTime(const sf::Keyboard::Key& k, Action * a)
{
  m_RTbinding.insert(std::pair<sf::Keyboard::Key, Action *>(k, a) );
}

void Controller::unsuscribeOneTime(const sf::Keyboard::Key& k)
{
  auto action = m_OTbinding.find(k);
  if(action != m_OTbinding.end() ){
    m_OTbinding.erase(action);
  }
  
}

void Controller::unsuscribeRealTime(const sf::Keyboard::Key& k)
{
  auto action = m_RTbinding.find(k);
  if(action != m_RTbinding.end() ){
    m_RTbinding.erase(action);
  }
}

void Controller::clearOneTime()
{
  m_OTbinding.clear();
}

void Controller::clearRealTime()
{
  m_RTbinding.clear();
}

std::queue<Action *> Controller::getActions()
{
  return m_actions;
}
