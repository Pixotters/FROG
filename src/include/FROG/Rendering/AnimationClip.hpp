#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace frog{

  class AnimationClip{
    
  protected:
    unsigned short m_sprite;
    unsigned int m_duration;
    sf::Transform m_transform;
    
  public:
    AnimationClip();
    virtual ~AnimationClip();
    // TODO delete getters / setters
    void setDuration(const unsigned int& d){ m_duration = d; };
    void setTransform(const sf::Transform& t){ m_transform = t; };
    unsigned int getDuration() const{ return m_duration; };
    sf::Transform getTransform() const{ return m_transform; };
    

  };

}

#endif
