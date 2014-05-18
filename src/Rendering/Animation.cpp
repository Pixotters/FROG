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
    m_clips.push_back(c);
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
