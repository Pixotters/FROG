#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace frog{

  /*!
   * AnimationClip is a part of an animation. They are composed by 
   * an id 'sprite" refering to a Clip in the owner Spritesheet, a 
   * duration (in number of frames), and transforms that can be applied.
   */
  struct AnimationClip{
    
    unsigned short sprite;
    unsigned short duration;
    sf::Transform transform;
    AnimationClip(unsigned short id = 0,
                  unsigned short duration = 1,
                  const sf::Transform& transform = sf::Transform::Identity);
    virtual ~AnimationClip();    

  };

}

#endif
