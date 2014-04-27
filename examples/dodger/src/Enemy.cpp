#include "Enemy.hpp"

#include "FROG/Random.hpp"

#include <SFML/Graphics.hpp>

#include <iostream> // TODO remove

using namespace frog;

Enemy::Enemy(const AppInfo& appinfo)
  : Element(appinfo)
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Red);
  phi::Physics * p = getComponent<phi::Physics>();
  p->addRotationForce(2.0f);
  p->addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 5.5) ) );

}

Enemy::~Enemy()
{
}



