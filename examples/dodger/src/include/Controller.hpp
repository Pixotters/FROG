#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Command.hpp"
#include "Input/Input.hpp"
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
  std::map<Input::Input * , Command *> m_RTbinding;
  std::map<Input::Input * , Command *> m_OTbinding;
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
  virtual void handleInputs();
  void suscribe(Input::Input *, Command *);
  void suscribeSimple(Input::Input *, Command *);
  void suscribeContinuous(Input::Input *, Command *);
  void unsuscribeSimple(Input::Input *);
  void unsuscribeContinuous(Input::Input *);
  void clearSimple();
  void clearContinuous();
  std::queue<Command *> getCommands();
  void addCommand(Command *);

private:
  void handleCont();
  void handleContinuous(Input::Input *, Command *);
  void handleContinuous(Input::KeyboardButton *, Command *);
  void handleContinuous(Input::MouseButton *, Command *);
  void handleContinuous(Input::JoystickButton *, Command *);
  void handleSimple();
  void handleButton(const sf::Keyboard::Key &, 
                    const Input::Button::Trigger& );
  void handleButton(const sf::Mouse::Button &, 
                    const Input::Button::Trigger& );
  void handleButton(const unsigned int &, 
                    const Input::Button::Trigger& );
};

#endif
