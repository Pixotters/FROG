#ifndef FROG_CTRL_CONTROLHANDLER_HPP
#define FROG_CTRL_CONTROLHANDLER_HPP

#include "FROG/Filter.hpp"

#include "FROG/Command.hpp"
#include "FROG/Control/KeyboardButton.hpp"
#include "FROG/Control/MouseButton.hpp"
#include "FROG/Control/KeyboardSimpleButton.hpp"
#include "FROG/Control/MouseSimpleButton.hpp"
#include "FROG/Control/JoystickButton.hpp"
#include "FROG/Control/JoystickSimpleButton.hpp"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <list>

namespace frog{

  namespace ctrl{


    class ControlHandler: virtual public Filter<Input *>
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
      ControlHandler(sf::Window * const = nullptr);
      virtual ~ControlHandler();
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
      virtual std::list<Input *> preprocess(std::list<Input *>);

    };

  }

}

#endif
