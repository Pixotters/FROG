#include "Controller.hpp"

#include "App.hpp"

#include "Input/Input.hpp"

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
      
      k = static_cast<sf::Keyboard::Key>(i);
    
      if(sf::Keyboard::isKeyPressed(k) )
        {
          /*          auto command = m_RTbinding.find(k);
                      if(command != m_RTbinding.end() )
                      {
                      m_commands.push( command->second );
                      }*/
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
        }else if( event.type == sf::Event::KeyPressed ){
        std::cerr << "Key pressed" << std::endl;
        handleKeyboardButton(event.key.code, Input::Button::PRESSED);        
      }else if (event.type == sf::Event::KeyReleased ){
        handleKeyboardButton(event.key.code, Input::Button::RELEASED);
      }else if(event.type == sf::Event::MouseButtonPressed ){
        handleMouseButton(event.mouseButton.button, Input::Button::PRESSED);
      }else if(event.type == sf::Event::MouseButtonReleased){
        handleMouseButton(event.mouseButton.button, Input::Button::RELEASED);
      }else if(event.type == sf::Event::JoystickButtonPressed ){
        handleJoystickButton(event.joystickButton.button, Input::Button::PRESSED);
      }else if(event.type == sf::Event::JoystickButtonReleased){
        handleJoystickButton(event.joystickButton.button, Input::Button::RELEASED);
      }

    }
    
}


void Controller::suscribeOneTime(Input::Input * i, Command * a)
{
  std::cerr << "input suscribed"<<std::endl;
  m_OTbinding.insert(std::pair<Input::Input *, Command *>(i, a) );
}

void Controller::suscribeRealTime(Input::Input * i, Command * a)
{
  m_RTbinding.insert(std::pair<Input::Input *, Command *>(i, a) );
}

void Controller::unsuscribeOneTime(Input::Input * i)
{
  auto command = m_OTbinding.find(i);
  if(command != m_OTbinding.end() ){
    m_OTbinding.erase(command);
  }
  
}

void Controller::unsuscribeRealTime(Input::Input * i)
{
  auto command = m_RTbinding.find(i);
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

void Controller::handleKeyboardButton(const sf::Keyboard::Key & button,
                                      const Input::Button::Trigger& trigger){
  Input::KeyboardButton * kb = nullptr;
  std::cerr << "searching among "<< m_OTbinding.size() <<"bindings" << std::endl;
  for(auto it = m_OTbinding.begin(); it != m_OTbinding.end(); ++it){
    if( (kb = dynamic_cast<Input::KeyboardButton *>( it->first )  )   ){
      if(kb->getTrigger() == trigger 
         && kb->getButton() == button){
        std::cerr<<"found !"<<std::endl;
        addCommand( it->second );
      }
    }
  }  
  std::cerr<<"finished !"<<std::endl;
}


void Controller::handleMouseButton(const sf::Mouse::Button & button,
                                   const Input::Button::Trigger& trigger){
  Input::MouseButton * mb = nullptr;
  for(auto it = m_OTbinding.begin(); it != m_OTbinding.end(); ++it){
    if( ( mb = dynamic_cast<Input::MouseButton *>( it->first )  )   ){
      if(mb->getTrigger() == trigger 
         && mb->getButton() == button){
        addCommand( it->second );
      }
    }
  }
}


void Controller::handleJoystickButton(const unsigned int & button,
                                      const Input::Button::Trigger& trigger){
  
  Input::JoystickButton * jb = nullptr;
  for(auto it = m_OTbinding.begin(); it != m_OTbinding.end(); ++it){
    if( (jb = dynamic_cast<Input::JoystickButton *>( it->first )  )   ){
      if(jb->getTrigger() == trigger 
         && jb->getButton() == button){
        addCommand( it->second );
      }
    }
  }

}


void Controller::addCommand(Command * c){
  m_commands.push( c );
}
