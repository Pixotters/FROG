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

#include "FROG/Collision/AABB.hpp"
#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/EndPoint.hpp"

namespace frog{

  AABB::AABB(Collider::PTR c) : owner(c) 
  {
    min[0] = new EndPoint(this, c->getXMin(), true);
    min[1] = new EndPoint(this, c->getYMin(), true);
    max[0] = new EndPoint(this, c->getXMax(), false);
    max[1] = new EndPoint(this, c->getYMax(), false);
  }

  AABB::~AABB () 
  { 
    if (min[0] != nullptr)
      {
        delete min[0];
        min[0] = nullptr;
      }
    if (min[1] != nullptr)
      {
        delete min[1];
        min[1] = nullptr;
      }
    if (max[0] != nullptr)
      {
        delete max[0];
        max[0] = nullptr;
      }
    if (max[1] != nullptr)
      {
        delete max[1];
        max[1] = nullptr;
      }
  }

  void AABB::updateEPValues() 
  {
    min[0]->value = owner->getXMin();
    min[1]->value = owner->getYMin();
    max[0]->value = owner->getXMax();
    max[1]->value = owner->getYMax();
  }

}
