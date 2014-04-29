#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace frog{

  struct AnimationClip{
    
    unsigned short sprite;
    unsigned short duration;
    sf::Transform transform;
    AnimationClip(const unsigned short& id = 0,
                  const unsigned short& duration = 1,
                  const sf::Transform& transform = sf::Transform::Identity);
    virtual ~AnimationClip();    

  };

}

#endif
