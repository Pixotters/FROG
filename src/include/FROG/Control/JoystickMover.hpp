#ifndef FROG_JOYSTICKMOVER_HPP
#define FROG_JOYSTICKMOVER_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
#include <SFML/Window/Joystick.hpp>
#include <SFML/System/Vector2.hpp>

namespace frog{

  class JoystickMover : virtual public Component
  {

  private:
    int up_velocity;
    int down_velocity;
    int left_velocity;
    int right_velocity;
    unsigned short deadzone;
    int joystick_id;
    sf::Joystick::Axis x;
    sf::Joystick::Axis y;

  public:
    JoystickMover(int up, int down, int left, int right, 
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned short deadzone = 25,
                  unsigned int joystickId = 0);
    JoystickMover(int velocity,
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned short deadzone = 25,
                  unsigned int joystickId = 0);
    virtual ~JoystickMover();
    sf::Vector2f getMovement() const;
    virtual void update(const ComponentHolder&); 

  };

}
#endif
