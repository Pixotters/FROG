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
