#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Command.hpp"
#include "Input/KeyboardButton.hpp"
#include "Input/MouseButton.hpp"
#include "Input/JoystickButton.hpp"

#include <SFML/Window.hpp>

#include <map>
#include <queue>

class Controller
{
  //// attributes ////
protected:
  std::map< Input::Input *, Command * > m_binding;
  std::queue< sf::Event > m_events;
  std::queue<Command * > m_commands;
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
  void suscribe(Input::Input *, Command *);
  void unsuscribe(Input::Input *);
  void clear();
  std::queue<Command *> getCommands();
  void addCommand(Command *);
  bool handle(Input::Input *);
  bool handle(Input::KeyboardButton *);
  bool handle(Input::MouseButton *);
  bool handle(Input::JoystickButton *);
};

#endif
