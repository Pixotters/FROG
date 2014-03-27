#include "Target.hpp"

#include "Main/Random.hpp"

#include <SFML/Graphics.hpp>

using namespace frog;

Target::Target()
  : Element()
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Green);
  phi::Physics * phi = getComponent<phi::Physics>();
  phi->addVelocity(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                                Random::get(-10, 10) / 10.f ) ); 
  phi->addAcceleration(  phi->getVelocity() / -100.0f );
  phi->addGrowth(sf::Vector2f(-0.005f, -0.005f) );

}

Target::~Target()
{
}


