#include "FROG/Physics/PhysicBody.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  PhysicBody::PhysicBody(float x, float y)
    : Component(), force(x, y) 
  {
  }

  PhysicBody::~PhysicBody()
  {
  }

  sf::Vector2f PhysicBody::getVelocity() const
  {
    return force;
  }

  void PhysicBody::applyForce(const sf::Vector2f& f)
  {
      force += f;
  }

  void PhysicBody::update(const ComponentHolder& parent)
  {
    auto tr = parent.getComponent<Transform>("TRANSFORM");
    tr->move(force);
  }


}
