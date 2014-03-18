#include "Control/Controller.hpp"
#include "App.hpp"
#include "Control/Input.hpp"

namespace ctrl{

  Controller::Controller(sf::Window * w)
    : AbstractController<Input, Command>(), m_window(w)
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

  bool Controller::handle(Input * i)
  {
    return false;
  }

  bool Controller::handle(KeyboardButton * b)
  {
    return (sf::Keyboard::isKeyPressed(b->getButton() )  );
  }

  bool Controller::handle(MouseButton * b)
  {
    return (sf::Mouse::isButtonPressed(b->getButton() )  );
  }

  bool Controller::handle(JoystickButton * b)
  {
    return (sf::Joystick::isButtonPressed(b->getID(), b->getButton() )  );
  }

  bool Controller::handle(KeyboardSimpleButton * b)
  {
    auto end = m_events.end();
    for(auto it = m_events.begin(); it != end; ++it)
      {
        if ( 
            ( (it->type == sf::Event::KeyPressed
               && b->getTrigger() == SimpleButton::PRESSED)
              || (it->type == sf::Event::KeyReleased
                  && b->getTrigger() == SimpleButton::RELEASED) )
            && (it->key.code == b->getButton() )  )
          {
            m_events.erase(it);
            return true;
          }
      }
    return false;
  }

  bool Controller::handle(MouseSimpleButton * b)
  {
    auto end = m_events.end();
    for(auto it = m_events.begin(); it != end; ++it)
      {
        if ( 
            ( (it->type == sf::Event::MouseButtonPressed
               && b->getTrigger() == SimpleButton::PRESSED)
              || (it->type == sf::Event::MouseButtonReleased
                  && b->getTrigger() == SimpleButton::RELEASED) )
            && (it->mouseButton.button == b->getButton() )  )
          {
            m_events.erase(it);
            return true;
          }
      }
    return false;
  }


  bool Controller::handle(JoystickSimpleButton * b)
  {
    auto end = m_events.end();
    for(auto it = m_events.begin(); it != end; ++it)
      {
        if ( 
            ( (it->type == sf::Event::JoystickButtonPressed
               && b->getTrigger() == SimpleButton::PRESSED)
              || (it->type == sf::Event::JoystickButtonReleased
                  && b->getTrigger() == SimpleButton::RELEASED) )
            && (it->joystickButton.button == b->getButton() )  )
          {
            m_events.erase(it);
            return true;
          }
      }
    return false;
  }



}
