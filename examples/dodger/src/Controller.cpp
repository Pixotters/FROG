#include "Controller.hpp"
#include "App.hpp"
#include "Input/Input.hpp"

#include "Input/SimpleButton.hpp"

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
  sf::Event event;
  m_events.clear();
  while(m_window->pollEvent(event) ){
    m_events.push_back(event);
  }
  AbstractController::handle();
}


////////// insert inputs after that ////

bool Controller::handle(Input::Input * i)
{
  return false;
}

bool Controller::handle(Input::KeyboardButton * b)
{
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

bool Controller::handle(Input::JoystickSimpleButton * b)
{
  auto end = m_events.end();
  sf::Event event;
  for(auto it = m_events.begin(); it != end; ++it)
    {
      if ( 
          ( (it->type == sf::Event::JoystickButtonPressed
             && b->getTrigger() == Input::SimpleButton::PRESSED)
            || (it->type == sf::Event::JoystickButtonReleased
                && b->getTrigger() == Input::SimpleButton::RELEASED) )
          && (it->joystickButton.button == b->getButton() )  )
        {
          m_events.erase(it);
          return true;
        }
    }
  return false;
}



