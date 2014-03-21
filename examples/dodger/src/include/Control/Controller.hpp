#ifndef CTRL_CONTROLLER_HPP
#define CTRL_CONTROLLER_HPP

#include "Filter.hpp"

#include "Command.hpp"
#include "Control/KeyboardButton.hpp"
#include "Control/MouseButton.hpp"
#include "Control/KeyboardSimpleButton.hpp"
#include "Control/MouseSimpleButton.hpp"
#include "Control/JoystickButton.hpp"
#include "Control/JoystickSimpleButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <list>

namespace ctrl{


  class Controller : virtual public Filter<Input>
  {
    //// attributes ////
  protected:
    std::list< sf::Event > m_events;
    int m_mouseX;
    int m_mouseY;
    int m_mouseDeltaX;
    int m_mouseDeltaY;
    sf::Window * const m_window;

    //// operations ////
  public:
    Controller(sf::Window * const = nullptr);
    virtual ~Controller();
    std::list<Input *> update();
    bool check(Input *);
    bool check(KeyboardButton *);
    bool check(MouseButton *);
    bool check(JoystickButton *);
    bool check(KeyboardSimpleButton *);
    bool check(MouseSimpleButton *);
    bool check(JoystickSimpleButton *);
    int getMouseX() const;
    int getMouseY() const;
    sf::Vector2i getMousePosition() const;
    int getMouseDeltaX() const;
    int getMouseDeltaY() const;
    sf::Vector2i getMouseDelta() const;
    float getJoystickAxis(const unsigned int& id,
                          const sf::Joystick::Axis& ax) const;

  protected:
    virtual void preprocess();

  };

}
#endif
