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

#include "FROG/Rendering/Animation.hpp"

namespace frog{

  Animation::Animation()
  {

  }

  Animation::Animation(const Animation& other)
  {
    for(AnimationClip it: other.m_clips)
      {
        m_clips.push_back(it);
      }
  }

  Animation::~Animation()
  {

  }

  void Animation::addClip(const AnimationClip& c)
  {
    m_clips.push_back( AnimationClip(c) );
  }

  std::vector<AnimationClip> Animation::getClips() const
  {
    return m_clips;
  }

  const AnimationClip& Animation::getClipAt(unsigned int i) const
  {
    // TODO random segfault here, because "m_clips" has invalid size/content
    const AnimationClip& clip = m_clips.at(i);
    return clip;
  }

  unsigned short Animation::getClipCount() const
  {
    return m_clips.size();
  }

}
