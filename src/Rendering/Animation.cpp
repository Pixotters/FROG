#include "FROG/Rendering/Animation.hpp"
#include "FROG/Debug.hpp"

namespace frog{

  Animation::Animation()
  {

  }

  Animation::Animation(const Animation& other)
  {
    auto end = other.m_clips.size();
    m_clips.resize(end);
    for(unsigned int it = 0; it < end; it++)
      {
        m_clips.at(it)= AnimationClip( other.m_clips.at(it) );
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
