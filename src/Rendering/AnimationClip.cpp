#include "FROG/Rendering/AnimationClip.hpp"

namespace frog{

  AnimationClip::AnimationClip(const unsigned short& _id,
                  const unsigned short& _duration,
                  const sf::Transform& _transform)
      : sprite(_id), duration(_duration), transform(_transform)
    {

    }


    AnimationClip::~AnimationClip()
    {
    
    }

}

