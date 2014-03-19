#include "Target.hpp"

#include "Random.hpp"

#include <SFML/Graphics.hpp>


Target::Target()
  : Element()
{
  m_boundingBox = new sf::CircleShape(30);
  m_boundingBox->setFillColor(sf::Color::Green);
  Physics * phi = getComponent<Physics>();
  phi->addVelocity(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                                Random::get(-10, 10) / 10.f ) ); 
  phi->addAcceleration(  phi->getVelocity() / -100.0f );
  phi->addGrowth(sf::Vector2f(-0.005f, -0.005f) );

}

Target::~Target()
{
}


