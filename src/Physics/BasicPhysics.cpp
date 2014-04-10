#include "FROG/Physics/BasicPhysics.hpp"

#include <iostream> // TODO remove

PhysicBody::PhysicBody(const float& x, const float& y) 
  : force(x, y) {
  force += sf::Vector2f(x, y);
  std::cout << "force : x,y "<< x << ","<< y<< std::endl;
}
