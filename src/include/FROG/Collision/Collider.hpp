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

#ifndef FROG_COLLIDER_HPP
#define FROG_COLLIDER_HPP

#include "FROG/Core/Component.hpp"
#include "FROG/Collision/Collision.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <memory>

namespace frog{

  /**
   * Collider is the base class for colliders and has to be implemented by
   * all objects meant to be added to Sweep And Prune collision manager.
   */
  class Collider : virtual public Component
  {

  public:
    typedef std::shared_ptr<Collider> PTR;

  public:

    std::function<void(Collision)> script;

    Collider(std::function<void(Collision)> = [](Collision){} );

    virtual ~Collider();

    /**
     * @brief Returns the smallest rectangle containing the collider.
     * @details Rectangles coordinates at based on the window it is in
     * @return A sf::FloatRect representing bounding rectangle of the collider.
     */
    virtual sf::FloatRect getBoundingBox() const = 0;

    /** @return the smallest value of a Collider on X axis */
    virtual float getXMin() const = 0;

    /** @return the smallest value of a Collider on Y axis */
    virtual float getYMin() const = 0;

    /** @return the greatest value of a Collider on X axis */
    virtual float getXMax() const = 0;

    /** @return the greatest value of a Collider on Y axis */
    virtual float getYMax() const = 0;

    virtual void update(const ComponentHolder&) = 0;

    void setScript(std::function<void(Collision)>);

    /*
     * @brief Function to trigger when this collider collides with another
     */
    void onCollision(const Collision&);

  };
}

#endif
