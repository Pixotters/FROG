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

#ifndef FROG_TRANSFORM_HPP
#define FROG_TRANSFORM_HPP

#include "FROG/Core/Component.hpp"

#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace frog{

  /*!
   * Transform holds data for sf::Transformable (position, rotation, scale) + a 
   * z-order. 
   */
  class Transform : virtual public Component,
                    virtual public sf::Transformable
  {

  public:
    typedef std::shared_ptr<Transform> PTR;

    //// operations ////
  public:

    int layer;

    Transform(int l = 0);

    Transform(const Transform&);

    virtual ~Transform();

    virtual void update(const ComponentHolder& parent);

    static PTR create(int l = 0);

  };

}

#endif

