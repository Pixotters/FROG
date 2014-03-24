#include "Control/ControlHandler.hpp"
#include "Control/Input.hpp"
#include "App.hpp" // TODO : see that dependencie
#include <SFML/Window/Event.hpp>


namespace ctrl{

  ControlHandler::ControlHandler(sf::Window * const w)
    : Filter<Input *>(), m_window(w)
  {

  }

  ControlHandler::~ControlHandler()
  {

  }

  std::list<Input *> ControlHandler::preprocess(std::list<Input *> in)
  {
    sf::Event event;
    m_events.clear();
    sf::Window * win = m_window;
    if(not win)
      win = App::instance()->getWindow(); // TODO : replace by a service locator
    while(win->pollEvent(event) ){
      if(event.type == sf::Event::Closed){
        /* TODO : close the program */
      } else if ( event.type == sf::Event::MouseMoved){
        m_mouseDeltaX = - m_mouseX;
        m_mouseDeltaY = - m_mouseY;
        m_mouseX = event.mouseMove.x;
        m_mouseY = event.mouseMove.y;
        m_mouseDeltaX += m_mouseX;
        m_mouseDeltaY += m_mouseY;
      }
      
      m_events.push_back(event);
    }
    return in;
  }

  std::list<Input *> ControlHandler::update()
  {
    return filter(m_check);
  }

  ////////// insert inputs after that ////

  bool ControlHandler::check(Input * i)
  {
    return i->check(this);
  }

  bool ControlHandler::check(KeyboardButton * b)
  {
    return (sf::Keyboard::isKeyPressed(b->getButton() )  );
  }

  bool ControlHandler::check(MouseButton * b)
  {
    return (sf::Mouse::isButtonPressed(b->getButton() )  );
  }

  bool ControlHandler::check(JoystickButton * b)
  {
    return (sf::Joystick::isButtonPressed(b->getID(), b->getButton() )  );
  }

  bool ControlHandler::check(KeyboardSimpleButton * b)
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

  bool ControlHandler::check(MouseSimpleButton * b)
  {
    auto end = m_events.end();
    for(auto it = m_events.begin(); it != end; ++it)
      {
        if ( ( (it->type == sf::Event::MouseButtonPressed
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


  bool ControlHandler::check(JoystickSimpleButton * b)
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

  int ControlHandler::getMouseX() const{
    return m_mouseX;
  } 

  int ControlHandler::getMouseY() const{
    return m_mouseY;
  }

  sf::Vector2i ControlHandler::getMousePosition() const{
    return sf::Vector2i(m_mouseX, m_mouseY);
  }

  int ControlHandler::getMouseDeltaX() const{
    return m_mouseX;
  } 

  int ControlHandler::getMouseDeltaY() const{
    return m_mouseY;
  }

  sf::Vector2i ControlHandler::getMouseDelta() const{
    return sf::Vector2i(m_mouseDeltaX, m_mouseDeltaY);
  }

  float ControlHandler::getJoystickAxis(const unsigned int& id,
                                    const sf::Joystick::Axis& ax) const{
    return sf::Joystick::getAxisPosition(id, ax);
  }



}
