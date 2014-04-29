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

    /*!
     * ControlHandler gets events that occur, and keeps a list of Input a state 
     * is interested in. 
     */
    class ControlHandler: virtual public Filter<Input *>
    {
      //// attributes ////
    protected:

      std::list< sf::Event > m_events;

      int m_mouseX;

      int m_mouseY;

      int m_mouseDeltaX;

      int m_mouseDeltaY;

      sf::Window & m_window;

      //// operations ////
    public:

      ControlHandler(sf::Window&);

      virtual ~ControlHandler();

      /*!
       * @brief Computes the list of interesting inputs that actually occured. 
       * @return List of Inputs that occurred. 
       */
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
      float getJoystickAxis(unsigned int id,
                            const sf::Joystick::Axis& ax) const;

    protected:
      virtual std::list<Input *> preprocess(std::list<Input *>);

    };

  }

}

#endif
