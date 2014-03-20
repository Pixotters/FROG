#ifndef CTRL_MOUSEBUTTON_HPP
#define CTRL_MOUSEBUTTON_HPP

#include "Control/Button.hpp"

#include <SFML/Window/Event.hpp>


namespace ctrl{

class Controller;

class MouseButton : virtual public Button
{

  //// attributes ////
protected : 
  sf::Mouse::Button m_button;

  //// operations ////
public:
  MouseButton(const sf::Mouse::Button&);
  virtual ~MouseButton();
  sf::Mouse::Button getButton() const;
  bool occurred(Controller *);
};

}
#endif
