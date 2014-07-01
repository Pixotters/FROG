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

#ifndef FROG_SPRITE_HPP
#define FROG_SPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>

namespace frog{

  /*!
   * Sprite allows to display an image easily. 
   */
  class Sprite : virtual public RenderingComponent
  {

  public:
    typedef std::shared_ptr<Sprite> PTR;

  public:
    std::shared_ptr<sf::Sprite> image;

  public:

    Sprite(const sf::Texture&);
    Sprite(const sf::Texture&, const sf::IntRect&);
    virtual ~Sprite();
    void setTexture(const sf::Texture&);
    void setClip(const sf::IntRect&);
    static PTR create(const sf::Texture&);
    static PTR create(const sf::Texture&, const sf::IntRect&);

  };

}

#endif
