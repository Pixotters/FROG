#include "FROG/Rendering/AnimationClip.hpp"

#include <iostream> //TODO remove

namespace frog{

  AnimationClip::AnimationClip(unsigned short _id,
                               unsigned short _duration,
                               const sf::Transform& _transform)
    : sprite(_id), duration(_duration), transform(_transform)
  {

  }

  AnimationClip::AnimationClip(const AnimationClip& other)
    : sprite(other.sprite), duration(other.duration), transform(other.transform)
  {
    std::cerr << "copying AnimClip" << std::endl;
  }


  AnimationClip::~AnimationClip()
  {
    
  }

}

