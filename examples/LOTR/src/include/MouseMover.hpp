#ifndef MOUSEMOVER_HPP
#define MOUSEMOVER_HPP

#include <FROG/Core/Component.hpp>
#include <FROG/Core/ComponentHolder.hpp>

#include <SFML/Window/Window.hpp>

class MouseMover : virtual public frog::Component
{

private:
  sf::Vector2i previous;

public:
  sf::Vector2i delta;

public:
  MouseMover();
  virtual ~MouseMover();
  virtual void update(const frog::ComponentHolder& parent);
  sf::Vector2i getPosition() const;
  void setPosition(const sf::Vector2i&);
  sf::Vector2i getPosition(const sf::Window&) const;
  void setPosition(const sf::Vector2i&, const sf::Window&);

};

#endif

