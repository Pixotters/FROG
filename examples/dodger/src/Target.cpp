#include "Target.hpp"

#include <SFML/Graphics.hpp>

Target::Target()
  : Element()
{
  m_boundingBox = new sf::CircleShape(30);
  m_boundingBox->setFillColor(sf::Color::Green);
}

Target::~Target()
{
}


