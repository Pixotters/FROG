#include "FROG/Physics/BasicPhysics.hpp"

PhysicBody::PhysicBody(const float& x, const float& y) 
  : force(x, y) {
  force += sf::Vector2f(x, y);
}
