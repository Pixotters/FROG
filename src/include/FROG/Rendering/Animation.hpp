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

#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/AnimationClip.hpp"

#include <vector>

namespace frog{

  /*!
   * Animation is a list of AnimationClips displayed one after the other in 
   * order to simulate movement. 
   */
  class Animation
  {

  public: //TODO protected
    std::vector<AnimationClip> m_clips;
  
  public:

    Animation();

    Animation(const Animation&);

    virtual ~Animation();

    /*!
     * @brief Adds a clip at the end of the current animation. 
     * @param clip AnimationClip to add.
     */
    void addClip(const AnimationClip& clip);

    std::vector<AnimationClip> getClips() const;

    /*!
     * @brief Return an AnimationClip at the given position. 
     * @details Throws exception "NoSuchAnimClip" if the given integer does not 
     * match an existing animation. 
     * @param i Index of the AnimationClip to get.
     * @return AnimationClip at position i.
     */
    const AnimationClip& getClipAt(unsigned int i) const;

    /*!
     * @brief Returns the number of clips the animation is made of.
     * @return Size of the animation (in number of contained AnimationClips).
     */
    unsigned short getClipCount() const;

  };

}

#endif
