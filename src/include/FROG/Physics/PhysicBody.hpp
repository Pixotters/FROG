/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_PHYSICBODY_HPP
#define FROG_PHYSICBODY_HPP

#include "FROG/Core/Component.hpp"

#include <SFML/System/Time.hpp>
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
    sf::Time& deltaTime;
    sf::Vector2f velocity;
    float rotation;
    sf::Vector2f growth;

  public:

    PhysicBody(sf::Time& dt,
               const sf::Vector2f& velocity = sf::Vector2f(0, 0),
               float rotation = 0.0f,
               const sf::Vector2f& growth = sf::Vector2f(0, 0) );

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

    static PTR create(sf::Time &, 
                      const sf::Vector2f& _velocity = sf::Vector2f(0, 0),
                      float _rotation = 0.0f,
                      const sf::Vector2f& _growth = sf::Vector2f(0, 0) );

  };

}

#endif
