#include "FROG/Rendering/Animation.hpp"

#include <iostream> // TODO remove

namespace frog{

  Animation::Animation()
  {

  }

  Animation::Animation(const Animation& other)
  {
    std::cerr << "copying animation " << std::endl;
    for(AnimationClip it: other.m_clips)
      {
        std::cerr << "copying one clip" << std::endl;
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
    std::cerr << "trying to get clip n°" << i << std::endl;
    std::cerr << "size is "<< m_clips.size() << std::endl;    
    const AnimationClip& clip = m_clips.at(i);
    return clip;
  }

  unsigned short Animation::getClipCount() const
  {
    return m_clips.size();
  }

}
