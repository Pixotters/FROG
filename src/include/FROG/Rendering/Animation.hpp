#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/Clip.hpp"
#include <SFML/Graphics/Texture.hpp>

#include <list>

namespace frog{

  class Animation
  {

  protected:
    sf::Texture& m_spritesheet;
    std::list<Clip *> m_clips;
  
  public:

    Animation(sf::Texture&);

    virtual ~Animation();

    void addClip(Clip * clip);

    void removeClip(Clip * clip);

    std::list<Clip *> getClips() const;

    sf::Texture& getSpritesheet() const;

  };

}

#endif
