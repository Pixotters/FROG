#include "Target.hpp"

#include "FROG/Random.hpp"
#include "FROG/Physics/PhysicBody.hpp"

#include <SFML/Graphics.hpp>

using namespace frog;

Target::Target(const AppInfo& appinfo)
  : Element(appinfo)
{
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Green);
  auto phi = getComponent<PhysicBody>("PHYSICS");
  phi->applyForce(sf::Vector2f(Random::get(-10, 10) / 10.f, 
                                Random::get(-10, 10) / 10.f ) ); 
  //  phi->addVelocity(sf::Vector2f(Random::get(-10, 10) / 10.f, 
  //                                Random::get(-10, 10) / 10.f ) ); 
  //  phi->addAcceleration(  phi->getVelocity() / -100.0f );
  //  phi->addGrowth(sf::Vector2f(-0.005f, -0.005f) );
  
}

Target::~Target()
{
}


