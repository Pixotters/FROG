#include "Controller.hpp"
#include "App.hpp"
#include "Input/Input.hpp"

#include <iostream>

Controller::Controller(sf::Window * w)
  : m_window(w)
{

}

Controller::~Controller()
{

}

void Controller::handleInputs()
{
  while(not m_commands.empty() )
    {
      m_commands.pop();
    }
  handleSimple();
  handleCont();
}

void Controller::handleCont()
{
  auto end = m_RTbinding.end();
  for(auto it = m_RTbinding.begin(); it != end; ++it)
    {
      handleContinuous(it->first, it->second);
    }
}

void Controller::handleContinuous(Input::Input * i, Command * c){
  Input::KeyboardButton * kb;
  Input::MouseButton * mb;
  Input::JoystickButton * jb;
  if( (kb = dynamic_cast<Input::KeyboardButton *>(i) )  )
    handleContinuous(kb, c);
  else if( (mb = dynamic_cast<Input::MouseButton *>(i) )  )
    handleContinuous(mb, c);
  else if( (jb = dynamic_cast<Input::JoystickButton *>(i) )  )
    handleContinuous(jb, c);
  else 
    std::cerr << "unknown continuous input" << std::endl;

}

void Controller::handleContinuous(Input::KeyboardButton * b, Command * c)
{
  if(sf::Keyboard::isKeyPressed(b->getButton() )  )
    addCommand(c);
}

void Controller::handleContinuous(Input::MouseButton * b, Command * c)
{
  if(sf::Mouse::isButtonPressed(b->getButton() )  )
    addCommand(c);
}

void Controller::handleContinuous(Input::JoystickButton * b, Command * c)
{
  if(sf::Joystick::isButtonPressed(b->getID(), b->getButton() )  )
    addCommand(c);
}



void Controller::handleSimple()
{
  sf::Event event;
  while( m_window -> pollEvent(event)  )
    {
      if( event.type ==  sf::Event::Closed )
        {
          App::instance()->exit();
        }else if( event.type == sf::Event::KeyPressed ){
        handleButton(event.key.code, Input::Button::PRESSED);        
      }else if (event.type == sf::Event::KeyReleased ){
        handleButton(event.key.code, Input::Button::RELEASED);
      }else if(event.type == sf::Event::MouseButtonPressed ){
        handleButton(event.mouseButton.button, Input::Button::PRESSED);
      }else if(event.type == sf::Event::MouseButtonReleased){
        handleButton(event.mouseButton.button, Input::Button::RELEASED);
      }else if(event.type == sf::Event::JoystickButtonPressed ){
        handleButton(event.joystickButton.button, Input::Button::PRESSED);
      }else if(event.type == sf::Event::JoystickButtonReleased){
        handleButton(event.joystickButton.button, Input::Button::RELEASED);
      }

    }
    
}

void Controller::suscribe(Input::Input * i, Command * a)
{
  if(i->isContinuous() ){
    suscribeContinuous(i, a);
  }else{
    suscribeSimple(i, a);
  }
}

void Controller::suscribeSimple(Input::Input * i, Command * a)
{
  m_OTbinding.insert(std::pair<Input::Input *, Command *>(i, a) );
}

void Controller::suscribeContinuous(Input::Input * i, Command * a)
{
  m_RTbinding.insert(std::pair<Input::Input *, Command *>(i, a) );
}

void Controller::unsuscribeSimple(Input::Input * i)
{
  auto command = m_OTbinding.find(i);
  if(command != m_OTbinding.end() ){
    m_OTbinding.erase(command);
  }
  
}

void Controller::unsuscribeContinuous(Input::Input * i)
{
  auto command = m_RTbinding.find(i);
  if(command != m_RTbinding.end() ){
    m_RTbinding.erase(command);
  }
}

void Controller::clearSimple()
{
  m_OTbinding.clear();
}

void Controller::clearContinuous()
{
  m_RTbinding.clear();
}

std::queue<Command *> Controller::getCommands()
{
  return m_commands;
}

void Controller::handleButton(const sf::Keyboard::Key & button,
                                      const Input::Button::Trigger& trigger){
  Input::KeyboardButton * kb = nullptr;
  auto end = m_OTbinding.end();
  for(auto it = m_OTbinding.begin(); it != end; ++it){
    if( (kb = dynamic_cast<Input::KeyboardButton *>( it->first )  )   ){
      if(kb->getTrigger() == trigger 
         && kb->getButton() == button){
        addCommand( it->second );
      }
    }
  }  

}


void Controller::handleButton(const sf::Mouse::Button & button,
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


void Controller::handleButton(const unsigned int & button,
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
