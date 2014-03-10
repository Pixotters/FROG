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
  while(not m_commands.empty() )
    {
      m_commands.pop();
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
          auto command = m_RTbinding.find(k);
          if(command != m_RTbinding.end() )
            {
              m_commands.push( command->second );
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
        auto command = m_OTbinding.find(event.key.code);
        if(command != m_OTbinding.end() ){         
          m_commands.push( command->second );
        }
      }
    
    }


}

void Controller::suscribeOneTime(const sf::Keyboard::Key& k, Command * a)
{
  m_OTbinding.insert(std::pair<sf::Keyboard::Key, Command *>(k, a) );
}

void Controller::suscribeRealTime(const sf::Keyboard::Key& k, Command * a)
{
  m_RTbinding.insert(std::pair<sf::Keyboard::Key, Command *>(k, a) );
}

void Controller::unsuscribeOneTime(const sf::Keyboard::Key& k)
{
  auto command = m_OTbinding.find(k);
  if(command != m_OTbinding.end() ){
    m_OTbinding.erase(command);
  }
  
}

void Controller::unsuscribeRealTime(const sf::Keyboard::Key& k)
{
  auto command = m_RTbinding.find(k);
  if(command != m_RTbinding.end() ){
    m_RTbinding.erase(command);
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

std::queue<Command *> Controller::getCommands()
{
  return m_commands;
}
