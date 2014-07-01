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

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  RenderingComponent::RenderingComponent(sf::Drawable * const d)
    : Component(), sf::Drawable(), sf::Transformable()
  {
    m_drawable.reset(d);
  }


  RenderingComponent::RenderingComponent(PTR_Drawable d)
    : Component(), sf::Drawable(), sf::Transformable(), m_drawable(d)
  {
  }

  RenderingComponent::~RenderingComponent()
  {
    m_drawable.reset();
  }

  void RenderingComponent::draw(sf::RenderTarget& rt, 
                                sf::RenderStates rs) const
  {
    rt.draw( *m_drawable, rs);
  }

  void RenderingComponent::update(const ComponentHolder& parent )
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    setOrigin( t->getOrigin() );
    setPosition( t->getPosition() );
    setRotation( t->getRotation() );
    setScale( t->getScale() );
  }

  RenderingComponent::PTR RenderingComponent::create(sf::Drawable * const d)
  {
    return PTR(new RenderingComponent(d) );
  }
  
  RenderingComponent::PTR RenderingComponent::create(PTR_Drawable d)
  {
    return PTR(new RenderingComponent(d) );
  }


}
