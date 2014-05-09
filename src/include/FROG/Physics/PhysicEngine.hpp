#ifndef FROG_PHYSICENGINE_HPP
#define FROG_PHYSICENGINE_HPP

#include "FROG/Physics/PhysicBody.hpp"
#include <SFML/System/Vector2.hpp>

namespace frog{


  class PhysicEngine {

  protected:

    static float dotProduct (const sf::Vector2f & v1, const sf::Vector2f & v2);

    // Projection of vector v on axis a
    // see http://www.metanetsoftware.com/technique/tutorialA.html#appendixA
    static sf::Vector2f projection(const sf::Vector2f& v, const sf::Vector2f& a);

  public:

    /**
     * Compute and apply reaction when two bodies collide. 
     * The order arguments are passed does not matter.
     * @param b1 first body colliding
     * @param b2 second body colliding
     * @param x X axis coordinate of collision point
     * @param y Y axis coordinate of collision point
     */

    static void reaction(PhysicBody * b1, PhysicBody * b2,
                  const sf::Vector2f & normal);
  };

}

#endif
