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

#ifndef FROG_AABB_HPP
#define FROG_AABB_HPP

#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/EndPoint.hpp"

#include <memory>

namespace frog{

  struct AABB {

  public:

    /** First minimum EndPoint is on x axis, second one is on y */
    EndPoint * min[2];

    /** Second minimum EndPoint is on x axis, second one is on y */
    EndPoint * max[2];

    /** Object the box is attached to */
    Collider::PTR owner;

    /**
     * Create the AABB corresponding to a collisionable object
     * @param c the object used to create the corresponding AABB
     */
    AABB(Collider::PTR c);

    virtual ~AABB ();

    /**
     * Update EndPoints values according to information provided by
     * owner and Collisionable API
     */
    void updateEPValues();

  };
}

#endif
