#include "FROG/Physics/PhysicBody.hpp"
#include "FROG/Transform.hpp"

#include <SFML/System/Vector2.hpp>

//const sf::Vector2f ZERO2F = sf::Vector2f(0, 0);

namespace frog{

  PhysicBody::PhysicBody(const sf::Vector2f& _velocity,
                         float _rotation,
                         const sf::Vector2f& _growth )
    : Component(), velocity(_velocity), rotation(_rotation), growth(_growth) 
  {
  }

  PhysicBody::~PhysicBody()
  {
  }

  sf::Vector2f PhysicBody::getVelocity() const
  {
    return velocity;
  }

  float PhysicBody::getRotation() const
  {
    return rotation;
  }

  sf::Vector2f PhysicBody::getGrowth() const
  {
    return growth;
  }

  void PhysicBody::addVelocity(const sf::Vector2f& v)
  {
    velocity += v;
  }

  void PhysicBody::addRotation(float r)
  {
    rotation += r;
  }

  void PhysicBody::addGrowth(const sf::Vector2f& g)
  {
    velocity += g;
  }

  void PhysicBody::reset()
  {
    velocity.x = 0;
    velocity.y = 0;
    rotation = 0.0f;
    growth.x = 0;
    growth.y = 0;
  }

  sf::Vector2f PhysicBody::resetVelocity()
  {
    auto old = sf::Vector2f(velocity.x, velocity.y);
    velocity.x = 0;
    velocity.y = 0;
    return old;
  }

  float PhysicBody::resetRotation()
  {
    auto old = rotation;
    rotation = 0.0f;
    return old;
  }
    
  sf::Vector2f PhysicBody::resetGrowth()
  {
    auto old = sf::Vector2f(growth.x, growth.y);
    growth.x = 0;
    growth.y = 0;
    return old;
  }

  void PhysicBody::update(const ComponentHolder& parent)
  {
    auto tr = parent.getComponent<Transform>("TRANSFORM");
    tr->move(velocity);
    tr->rotate(rotation);
    tr->setScale(tr->getScale() + growth);
  }


}
