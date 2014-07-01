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

#include "FROG/Collision/BoxCollider.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  BoxCollider::BoxCollider(const sf::Vector2f& dimensions,
                           const sf::Vector2f& _gap,
                           std::function<void(Collision)> fun )
    : Collider(fun), gap(_gap)
  {
    rectangle.setSize( dimensions );
  }

  BoxCollider::~BoxCollider()
  {
  }

  sf::FloatRect BoxCollider::getBoundingBox() const
  {
    return rectangle.getGlobalBounds();
  }

  float BoxCollider::getXMin() const
  {
    return rectangle.getGlobalBounds().left;
  }

  float BoxCollider::getYMin() const
  {
    return rectangle.getGlobalBounds().top;
  }

  float BoxCollider::getXMax() const
  {
    auto gb = rectangle.getGlobalBounds();
    return gb.left + gb.width;
  }

  float BoxCollider::getYMax() const
  {
    auto gb = rectangle.getGlobalBounds();
    return gb.top + gb.height;
  }

  void BoxCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // synchronizing transform with parent's transform
    rectangle.setOrigin( rectangle.getSize() / 2.0f );
    rectangle.setScale( t->getScale() );
    rectangle.setPosition( t->getPosition() + gap );
    rectangle.setRotation( t->getRotation() );
  }

  void BoxCollider::resize(const sf::Vector2f& newsize)
  {
    rectangle.setSize(newsize);
  }

  void BoxCollider::setGap(const sf::Vector2f& newgap)
  {
    gap = newgap;
  }

  BoxCollider::PTR BoxCollider::create(const sf::Vector2f& dimensions,
                                       const sf::Vector2f& gap,
                                       std::function<void(Collision)> fun)
  {
    return PTR(new BoxCollider(dimensions, gap, fun) );
  }

}
