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

#include "FROG/Core/Transform.hpp"


namespace frog{

  Transform::Transform(int _layer) 
    : Component(), sf::Transformable() , layer(_layer)
  {
    setPosition(0, 0);
    setRotation(0);
    setScale(1.0f, 1.0f);
  }

  Transform::Transform(const Transform& other)
  {
    setPosition( other.getPosition() );
    setRotation( other.getRotation() );
    setScale( other.getScale() );
    layer = other.layer;
  }

  Transform::~Transform()
  { 
  }

  void Transform::update(const ComponentHolder&)
  { 
    
  }

  Transform::PTR Transform::create(int l)
  {
    return PTR(new Transform(l) );
  }

}
