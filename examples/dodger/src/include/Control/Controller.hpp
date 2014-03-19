#ifndef CTRL_CONTROLLER_HPP
#define CTRL_CONTROLLER_HPP

#include "Control/AbstractController.hpp"

#include "Command.hpp"
#include "Control/KeyboardButton.hpp"
#include "Control/MouseButton.hpp"
#include "Control/KeyboardSimpleButton.hpp"
#include "Control/MouseSimpleButton.hpp"
#include "Control/JoystickButton.hpp"
#include "Control/JoystickSimpleButton.hpp"

#include <SFML/Window.hpp>

#include <map>
#include <queue>
#include <list>

namespace ctrl{

  class Controller : virtual public AbstractController<Input, Command>
  {
    //// attributes ////
  protected:
    std::list< sf::Event > m_events;
    int m_mouseX;
    int m_mouseY;
    int m_deltaMouseX;
    int m_deltaMouseY;
    sf::Window * const m_window;

    //// operations ////
  public:
    Controller(sf::Window * const = nullptr);
    virtual ~Controller();
    virtual void update();
    bool handle(Input *);
    bool handle(KeyboardButton *);
    bool handle(MouseButton *);
    bool handle(JoystickButton *);
    bool handle(KeyboardSimpleButton *);
    bool handle(MouseSimpleButton *);
    bool handle(JoystickSimpleButton *);
  };

}
#endif
