#include "FROG/Rendering/Animation.hpp"

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

  const AnimationClip& Animation::getClipAt(const unsigned int& i) const
  {
    std::cerr << "ANIMATION : getting clip "<<i<<"/"<<m_clips.size() << std::endl;
    return m_clips.at(i);
  }

  unsigned short Animation::getClipCount() const
  {
    return m_clips.size();
  }

}
