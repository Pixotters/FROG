#ifndef FROG_ANIMATION_CLIP_HPP
#define FROG_ANIMATION_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace frog{

  class AnimationClip{
    
  protected:
    unsigned short m_sprite;
    unsigned short m_duration;
    sf::Transform m_transform;
    
  public:
    AnimationClip(const unsigned short& id = 0,
                  const unsigned short& duration = 1,
                  const sf::Transform& scale = sf::Transform::Identity);
    virtual ~AnimationClip();
    // TODO delete getters / setters
    void setSprite(const unsigned short& id){ m_sprite = id; };
    void setDuration(const unsigned int& d){ m_duration = d; };
    void setTransform(const sf::Transform& t){ m_transform = t; };
    unsigned short getSprite() const{ return m_sprite; };
    unsigned int getDuration() const{ return m_duration; };
    sf::Transform getTransform() const{ return m_transform; };
    

  };

}

#endif
