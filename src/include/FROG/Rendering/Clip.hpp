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

#ifndef FROG_CLIP_HPP
#define FROG_CLIP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>


namespace frog{

  /*!
   * Clips are parts of a Spritesheet. They are defined by a rectangle telling 
   * which prt of an image it should be extracted from, and a hotpoint, 
   * representing a gap between position of the owner, and position where image 
   * should be displayed. 
   */
  struct Clip{
    
    sf::IntRect rectangle;
    sf::Vector2i hotpoint;
    
    Clip(int x = 0, int y = 0, 
         unsigned w = 0, unsigned h = 0,
         int hx = 0, int hy = 0);
    Clip(const Clip&);
    virtual ~Clip();
    
  };

}

#endif
