#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/AnimationClip.hpp"
#include <SFML/Graphics/Texture.hpp>

#include <list>

namespace frog{

  class Animation
  {

  protected:
    std::list<AnimationClip *> m_clips;
  
  public:

    Animation();

    virtual ~Animation();

    void addClip(AnimationClip * clip);

    void removeClip(AnimationClip * clip);

    std::list<AnimationClip *> getClips() const;

  };

}

#endif
