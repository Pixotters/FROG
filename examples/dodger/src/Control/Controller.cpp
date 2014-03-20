#include "Control/Controller.hpp"
#include "Control/Input.hpp"
#include "App.hpp" // TODO : see that dependencie
#include <SFML/Window/Event.hpp>


namespace ctrl{

  Controller::Controller(sf::Window * const w)
    : AbstractController<Input, Command>(), m_window(w)
  {

  }

  Controller::~Controller()
  {

  }

  void Controller::update()
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
    AbstractController::update();
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

  int Controller::getMouseX() const{
    return m_mouseX;
  } 

  int Controller::getMouseY() const{
    return m_mouseY;
  }

  sf::Vector2i Controller::getMousePosition() const{
    return sf::Vector2i(m_mouseX, m_mouseY);
  }

  int Controller::getMouseDeltaX() const{
    return m_mouseX;
  } 

  int Controller::getMouseDeltaY() const{
    return m_mouseY;
  }

  sf::Vector2i Controller::getMouseDelta() const{
    return sf::Vector2i(m_mouseDeltaX, m_mouseDeltaY);
  }

  float Controller::getJoystickAxis(const unsigned int& id,
                                    const sf::Joystick::Axis& ax) const{
    return sf::Joystick::getAxisPosition(id, ax);
  }

}
