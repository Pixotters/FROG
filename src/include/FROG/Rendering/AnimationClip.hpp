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

#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>

namespace frog{

  /*!
   * AnimationClip is a part of an animation. They are composed by 
   * an id 'sprite" refering to a Clip in the owner Spritesheet, a 
   * duration (in number of frames), and transforms that can be applied.
   */
  struct AnimationClip{
    
    unsigned short sprite;
    sf::Time duration;
    sf::Transform transform;
    AnimationClip(unsigned short id = 0,
                  sf::Time duration = sf::seconds(1.0f/60.0f),
                  const sf::Transform& transform = sf::Transform::Identity);
    AnimationClip(const AnimationClip& other);
    virtual ~AnimationClip();    

  };

}

#endif
