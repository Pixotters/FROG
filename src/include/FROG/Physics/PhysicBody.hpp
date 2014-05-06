#ifndef FROG_PHYSICBODY_HPP
#define FROG_PHYSICBODY_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
//#include "FROG/Physics/BasicPhysics.hpp"

#include <SFML/System/Vector2.hpp>

namespace frog{
  /**
   * This first physic engine only deals with basic collisions
   * (i.e. rotations are not supported yet)
   */
  class PhysicBody : virtual public Component
  {

    /**
     * This class assumes that we are able to give coordinate of collision
     * point.
     */

    friend class PhysicEngine;

  protected:

    sf::Vector2f force;

  public:

    PhysicBody(float x = 0, float y = 0);

    virtual ~PhysicBody();

    sf::Vector2f getVelocity() const;

    void update(const ComponentHolder& parent);

    /* FIXME:
     * making it virtual could be interesting if we want some objects
     * to act different, but we want this? */
    virtual void applyForce(const sf::Vector2f & f);


  };

}

#endif
