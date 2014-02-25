#include "Enemy.hpp"

#include <SFML/Graphics.hpp>

Enemy::Enemy()
  : Element()
{
  m_boundingBox = new sf::CircleShape(45);
  m_boundingBox->setFillColor(sf::Color::Red);
}

Enemy::~Enemy()
{
}


