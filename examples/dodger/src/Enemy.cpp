#include "Enemy.hpp"

#include <SFML/Graphics.hpp>

Enemy::Enemy()
  : Element()
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Red);
}

Enemy::~Enemy()
{
}


