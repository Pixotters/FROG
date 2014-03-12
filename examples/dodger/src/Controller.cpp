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

void Controller::handle()
{
  while(not m_commands.empty() )
    {
      m_commands.pop();
    }
  sf::Event event;
  while(m_window->pollEvent(event) ){
    m_events.push(event);
  }
  auto end = m_binding.end();
  for(auto it = m_binding.begin(); it != end; ++it)
    {
      std::cout << "have to handle an input" << std::endl;
      if (it->first->handle(this) )
        {
          std::cout << "success" << std::endl;
          addCommand(it->second );
        }
    }
}


void Controller::suscribe(Input::Input * i, Command * a)
{
  m_binding.insert(std::pair<Input::Input *, Command *>(i, a) );
}


void Controller::unsuscribe(Input::Input * i)
{

}

void Controller::clear()
{
  m_binding.clear();
}


std::queue<Command *> Controller::getCommands()
{
  return m_commands;
}

void Controller::addCommand(Command * c){
  m_commands.push( c );
}

////////// insert inputs after that ////

bool Controller::handle(Input::Input * i)
{
  std::cerr << "Controller - handle : unknown input type"<< std::endl;
  return false;
}

bool Controller::handle(Input::KeyboardButton * b)
{
  std::cout << "Controller - handle : button "<< std::endl;
  return (sf::Keyboard::isKeyPressed(b->getButton() )  );
}

bool Controller::handle(Input::MouseButton * b)
{
  return (sf::Mouse::isButtonPressed(b->getButton() )  );
}

bool Controller::handle(Input::JoystickButton * b)
{
  return (sf::Joystick::isButtonPressed(b->getID(), b->getButton() )  );
}

/*
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
*/
