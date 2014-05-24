#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>

namespace frog{

  /*!
   * AnimationClip is a part of an animation. They are composed by 
   * an id 'sprite" refering to a Clip in the owner Spritesheet, a 
   * duration (in number of frames), and transforms that can be applied.
   */
  struct AnimationClip{
    
    unsigned short sprite;
    sf::Time duration;
    sf::Transform transform;
    AnimationClip(unsigned short id = 0,
                  sf::Time duration = sf::seconds(1.0f/60.0f),
                  const sf::Transform& transform = sf::Transform::Identity);
    AnimationClip(const AnimationClip& other);
    virtual ~AnimationClip();    

  };

}

#endif
