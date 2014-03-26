#include "Enemy.hpp"

#include "Main/Random.hpp"

#include <SFML/Graphics.hpp>


using namespace frog;

Enemy::Enemy()
  : Element()
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Red);
  phi::Physics * p = getComponent<phi::Physics>();
  p->addRotationForce(5.0f);
  p->addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 7) ) );

}

Enemy::~Enemy()
{
}



