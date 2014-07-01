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

#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Core/Transform.hpp"

#include <memory>

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : RenderingComponent(new sf::Sprite)
  {
    image = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    image->setTexture(texture);
  }

  Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& clip)
    : RenderingComponent(new sf::Sprite)
  {
    image = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    image->setTexture(texture);
    image->setTextureRect(clip);
  }
  
  Sprite::~Sprite()
  {

  }
  
  void Sprite::setTexture(const sf::Texture& tex)
  {
    image->setTexture(tex);
  }

  void Sprite::setClip(const sf::IntRect& clip)
  {
    image->setTextureRect(clip);
  }

  Sprite::PTR Sprite::create(const sf::Texture& tex)
  {
    return PTR(new Sprite(tex) );
  }

  Sprite::PTR Sprite::create(const sf::Texture& tex, const sf::IntRect& clip)
  {
    return PTR(new Sprite(tex, clip) );
  }

}
