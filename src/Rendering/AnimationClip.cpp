#include "FROG/Rendering/AnimationClip.hpp"

namespace frog{

  AnimationClip::AnimationClip(unsigned short _id,
                               sf::Time _duration,
                               const sf::Transform& _transform)
    : sprite(_id), duration(_duration), transform(_transform)
  {

  }

  AnimationClip::AnimationClip(const AnimationClip& other)
    : sprite(other.sprite), duration(other.duration), transform(other.transform)
  {
  }


  AnimationClip::~AnimationClip()
  {
    
  }

}

