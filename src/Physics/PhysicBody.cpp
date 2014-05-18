#include "FROG/Physics/PhysicBody.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

#include <SFML/System/Vector2.hpp>

namespace frog{

  PhysicBody::PhysicBody(sf::Time& dt,
                         const sf::Vector2f& _velocity,
                         float _rotation,
                         const sf::Vector2f& _growth )
    : Component(), 
      deltaTime(dt),
      velocity(_velocity), rotation(_rotation), growth(_growth) 
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
    growth += g;
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
    growth.x = 1.0f;
    growth.y = 1.0f;
    return old;
  }

  void PhysicBody::update(const ComponentHolder& parent)
  {
    auto tr = parent.getComponent<Transform>("TRANSFORM");
    float sec = deltaTime.asSeconds();
    tr->move(velocity * sec);
    tr->rotate(rotation * sec);
    tr->scale(growth * sec);
  }

  PhysicBody::PTR PhysicBody::create(sf::Time& _dt,
                                     const sf::Vector2f& _velocity,
                                     float _rotation,
                                     const sf::Vector2f& _growth )
  {
    return PTR(new PhysicBody(_dt, _velocity, _rotation, _growth) );
  }

}
