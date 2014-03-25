#include "Enemy.hpp"

#include "Random.hpp"

#include <SFML/Graphics.hpp>


using namespace frog;

Enemy::Enemy()
  : Element()
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Red);
  getComponent<Physics>()->addRotationForce(5.0f);
  getComponent<Physics>()->addVelocity(sf::Vector2f(Random::get(-2,2), Random::get(4, 7) ) );

}

Enemy::~Enemy()
{
}



