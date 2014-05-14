#ifndef FROG_PHYSICBODY_HPP
#define FROG_PHYSICBODY_HPP

#include "FROG/Core/Component.hpp"

#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{
  /**
   * This first physic engine only deals with basic collisions
   * (i.e. rotations are not supported yet)
   */
  class PhysicBody : virtual public Component
  {

  public:
    typedef std::shared_ptr<PhysicBody> PTR;

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
               const sf::Vector2f& growth = sf::Vector2f(1.0, 1.0) );

    virtual ~PhysicBody();

    sf::Vector2f getVelocity() const;

    float getRotation() const;

    sf::Vector2f getGrowth() const;

    void update(const ComponentHolder& parent);

    virtual void addVelocity(const sf::Vector2f & v);

    virtual void addRotation(float r);

    virtual void addGrowth(const sf::Vector2f & g);

    void reset();

    sf::Vector2f resetVelocity();

    float resetRotation();
    
    sf::Vector2f resetGrowth();

    PTR create(const sf::Vector2f& _velocity = sf::Vector2f(0, 0),
               float _rotation = 0.0f,
               const sf::Vector2f& _growth = sf::Vector2f(1.0, 1.0) );

  };

}

#endif
