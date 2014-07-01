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
    growth.x = 0.0f;
    growth.y = 0.0f;
    return old;
  }

  void PhysicBody::update(const ComponentHolder& parent)
  {
    auto tr = parent.getComponent<Transform>("TRANSFORM");
    float sec = deltaTime.asSeconds();
    tr->move(velocity * sec);
    tr->rotate(rotation * sec);
    auto previous_scale = tr->getScale();
    tr->setScale( previous_scale+(growth * sec) );
  }

  PhysicBody::PTR PhysicBody::create(sf::Time& _dt,
                                     const sf::Vector2f& _velocity,
                                     float _rotation,
                                     const sf::Vector2f& _growth )
  {
    return PTR(new PhysicBody(_dt, _velocity, _rotation, _growth) );
  }

}
