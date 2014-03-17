#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "AbstractController.hpp"

#include "Command.hpp"
#include "Input/KeyboardButton.hpp"
#include "Input/MouseButton.hpp"
#include "Input/JoystickButton.hpp"
#include "Input/JoystickSimpleButton.hpp"

#include <SFML/Window.hpp>

#include <map>
#include <queue>
#include <list>

class Controller : virtual public AbstractController<Input::Input, Command>
{
  //// attributes ////
protected:
  std::list< sf::Event > m_events;
  int m_mouseX;
  int m_mouseY;
  int m_deltaMouseX;
  int m_deltaMouseY;
  sf::Window * m_window;

  //// operations ////
public:
  Controller(sf::Window *);
  virtual ~Controller();
  virtual void handle();
  bool handle(Input::Input *);
  bool handle(Input::KeyboardButton *);
  bool handle(Input::MouseButton *);
  bool handle(Input::JoystickButton *);
  bool handle(Input::JoystickSimpleButton *);
};

#endif
