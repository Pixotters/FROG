#ifndef FROG_PHYSICBODY_HPP
#define FROG_PHYSICBODY_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
//#include "FROG/Physics/BasicPhysics.hpp"

#include <SFML/System/Vector2.hpp>

const sf::Vector2f ZERO2F = sf::Vector2f(0, 0);

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

    sf::Vector2f velocity;
    float rotation;
    sf::Vector2f growth;

  public:

    PhysicBody(const sf::Vector2f& velocity = sf::Vector2f(0, 0),
               float rotation = 0.0f,
               const sf::Vector2f& growth = sf::Vector2f(0, 0) );

    virtual ~PhysicBody();

    sf::Vector2f getVelocity() const;

    float getRotation() const;

    sf::Vector2f getGrowth() const;

    void update(const ComponentHolder& parent);

    /* FIXME:
     * making it virtual could be interesting if we want some objects
     * to act different, but we want this? */
    virtual void addVelocity(const sf::Vector2f & v);

    virtual void addRotation(float r);

    virtual void addGrowth(const sf::Vector2f & g);

    void reset();

    sf::Vector2f resetVelocity();

    float resetRotation();
    
    sf::Vector2f resetGrowth();

  };

}

#endif
