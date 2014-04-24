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
    m_clips.remove(c);
  }

  std::list<AnimationClip *> Animation::getClips() const
  {
    return m_clips;
  }


}
