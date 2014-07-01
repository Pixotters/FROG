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

    sf::Vector2f v = b1->velocity - b2->velocity;
    sf::Vector2f n = dotProduct (v, normal) * normal * -(1 + ELASTICITY);

    b1->addVelocity (n * 0.5f);
    b2->addVelocity (- n * 0.5f);

  }


}
