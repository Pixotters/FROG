#include "FROG/Rendering/Animation.hpp"

namespace frog{

  Animation::Animation()
  {

  }

  Animation::~Animation()
  {

  }

  void Animation::addClip(AnimationClip * c)
  {
    m_clips.push_back(c);
  }

  void Animation::removeClip(AnimationClip * c)
  {
    // TODO
    //    m_clips.remove(c);
  }

  std::vector<AnimationClip *> Animation::getClips() const
  {
    return m_clips;
  }


  AnimationClip * Animation::getClipAt(const unsigned int& i) const
  {
    return m_clips.at(i);
  }

  unsigned short Animation::getClipCount() const
  {
    return m_clips.size();
  }

}
