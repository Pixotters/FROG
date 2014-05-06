#include "FROG/Physics/PhysicEngine.hpp"
#include <SFML/System/Vector2.hpp>

namespace frog{

  float PhysicEngine::dotProduct (const sf::Vector2f & v1, 
                                  const sf::Vector2f & v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }

  sf::Vector2f PhysicEngine::projection (const sf::Vector2f & v, 
                                         const sf::Vector2f & a) {
    auto tmp = (v.x*a.x + v.y*a.y) / (v.x*v.x + v.y*v.y);
    return sf::Vector2f(tmp * v.x, tmp * v.y);
  }

  void PhysicEngine::reaction(PhysicBody * b1, PhysicBody * b2,
                              const sf::Vector2f & normal) {


    // see http://elancev.name/oliver/2D%20polygon.htm#tut4
    // ELASTICITY should be replaced by a object property
    // also, here we assume thant b1 and b2 have the same elasticity
#define ELASTICITY 1.0f

    sf::Vector2f v = b1->force - b2->force;
    sf::Vector2f n = dotProduct (v, normal) * normal * -(1 + ELASTICITY);

    b1->applyForce (n * 0.5f);
    b2->applyForce (- n * 0.5f);

  }


}
