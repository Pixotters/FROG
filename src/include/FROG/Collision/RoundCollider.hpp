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

#ifndef FROG_ROUNDCOLLIDER_HPP
#define FROG_ROUNDCOLLIDER_HPP

#include "FROG/Collision/Collider.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{

  class RoundCollider : virtual public Collider
  {

  public:
    typedef std::shared_ptr<RoundCollider> PTR;

  public:
    /// the underlying circle
    sf::CircleShape circle;
    /// the gap between origin of parent and origin of the box
    sf::Vector2f gap;


  public:
    RoundCollider(float rad = 1.0f,
                  const sf::Vector2f& gap = sf::Vector2f(0,0),
                  std::function<void(Collision)> = [](Collision){} );
    virtual ~RoundCollider();
    virtual sf::FloatRect getBoundingBox() const;
    virtual float getXMin() const;
    virtual float getYMin() const;
    virtual float getXMax() const;
    virtual float getYMax() const;
    virtual void update(const ComponentHolder&);
    virtual void resize(float);
    virtual void setGap(const sf::Vector2f&);
    static PTR create(float rad = 1.0f,
                      const sf::Vector2f& gap = sf::Vector2f(0,0),
                      std::function<void(Collision)> = [](Collision){} );


  };

}

#endif
