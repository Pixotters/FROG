#ifndef FROG_JOYSTICKMOVER_HPP
#define FROG_JOYSTICKMOVER_HPP

#include "FROG/Component.hpp"
#include <SFML/Window/Joystick.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{

  class JoystickMover : virtual public Component
  {

  public:
    typedef std::shared_ptr<JoystickMover> PTR;

  private:
    int up_velocity;
    int down_velocity;
    int left_velocity;
    int right_velocity;
    int joystick_id;
    unsigned short deadzone;
    sf::Joystick::Axis x;
    sf::Joystick::Axis y;

  public:
    JoystickMover(int up, int down, int left, int right, 
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned int joystickId = 0,
                  unsigned short deadzone = 25);
    JoystickMover(int velocity,
                  sf::Joystick::Axis x,
                  sf::Joystick::Axis y,
                  unsigned int joystickId = 0,
                  unsigned short deadzone = 25);
    virtual ~JoystickMover();
    sf::Vector2f getMovement() const;
    virtual void update(const ComponentHolder&); 
    static PTR create(int up, int down, int left, int right, 
                      sf::Joystick::Axis x,
                      sf::Joystick::Axis y,
                      unsigned int joystickId = 0,
                      unsigned short deadzone = 25);
    static PTR create(int velocity,
                      sf::Joystick::Axis x,
                      sf::Joystick::Axis y,
                      unsigned int joystickId = 0,
                      unsigned short deadzone = 25
                      );
  };

}
#endif
