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

  //// operations ////
public:
  Controller();
  virtual ~Controller();
  virtual void handleInputs(sf::Window *);
  void suscribeOneTime(Input::Input *, Command *);
  void suscribeRealTime(Input::Input *, Command *);
  void unsuscribeOneTime(Input::Input *);
  void unsuscribeRealTime(Input::Input *);
  void clearOneTime();
  void clearRealTime();
  std::queue<Command *> getCommands();
  void addCommand(Command *);

private:
  void handleRealTime();
  void handleOneTime(sf::Window *);
  void handleKeyboardButton(const sf::Keyboard::Key &, 
                            const Input::Button::Trigger& );
  void handleMouseButton(const sf::Mouse::Button &, 
                         const Input::Button::Trigger& );
  void handleJoystickButton(const unsigned int &, 
                            const Input::Button::Trigger& );
};

#endif
