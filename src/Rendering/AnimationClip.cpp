#include "FROG/Rendering/AnimationClip.hpp"

namespace frog{

  AnimationClip::AnimationClip(const unsigned short& id,
                               const unsigned short& duration,
                               const sf::Transform& trans)
    : m_sprite(id), m_duration(duration), m_transform(trans)
  {

  }

  AnimationClip::~AnimationClip()
  {
  }

}

