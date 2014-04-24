#ifndef FROG_CLIP_HPP
#define FROG_CLIP_HPP

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Rect.hpp>


namespace frog{

  class Clip{
    
  protected:
    unsigned int m_duration;
    sf::Rect<int> m_clip;
    sf::Transform m_transform;
    
  public:
    Clip();
    virtual ~Clip();
    // TODO delete getters / setters
    void setDuration(const unsigned int& d){ m_duration = d; };
    void setTransform(const Transform& t){ m_transform = d; };
    void setClip(const sf::Rect<int>& r){ m_clip = r; };
    unsigned int getDuration() const{ return m_duration; };
    sf::Transform getTransform() const{ return m_transform; };
    sf::Rect<int> getClip() const{ return m_clip; };
    

  };

}

#endif
