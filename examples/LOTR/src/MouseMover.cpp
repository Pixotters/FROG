#include "MouseMover.hpp"

#include <FROG/Core/Transform.hpp>

#include <SFML/Window/Mouse.hpp>

using namespace frog;

MouseMover::MouseMover()
  : Component(),
    previous( sf::Vector2i(0,0) ),
    delta( sf::Vector2i(0,0) )
{
}

MouseMover::~MouseMover()
{
}

void MouseMover::update(const ComponentHolder& parent)
{
  auto pos = getPosition();
  delta = pos - previous;
  previous = pos;
  auto vec = static_cast<sf::Vector2f>(delta);
  parent.getComponent<Transform>("TRANSFORM")->move( vec );
}

sf::Vector2i MouseMover::getPosition() const
{
  return sf::Mouse::getPosition();
}

void MouseMover::setPosition(const sf::Vector2i& newpos)
{
  sf::Mouse::setPosition(newpos);
}

sf::Vector2i MouseMover::getPosition(const sf::Window& win) const
{
  return sf::Mouse::getPosition(win);
}

void MouseMover::setPosition(const sf::Vector2i& newpos, const sf::Window& win)
{
  sf::Mouse::setPosition(newpos, win);
}
