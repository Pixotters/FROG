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

#include "FROG/Collision/Collider.hpp"

namespace frog{

  Collider::Collider(std::function<void(Collision)> fun)
    : Component()
  {
    script = fun;
  }

  Collider::~Collider()
  {

  }

  void Collider::setScript(std::function<void(Collision)> fun)
  {
    script = fun;
  }

  void Collider::onCollision(const Collision& c)
  {
    // TODO : this should not be check again ?
    auto bb1 = c.first->getComponent<Collider>("COLLIDER")->getBoundingBox();
    auto bb2 = c.second->getComponent<Collider>("COLLIDER")->getBoundingBox();
    if ( bb1.intersects(bb2) )
      script(c);

  }

}
