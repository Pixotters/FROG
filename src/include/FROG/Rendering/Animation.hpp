#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/AnimationClip.hpp"
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace frog{

  class Animation
  {

  protected:
    std::vector<AnimationClip> m_clips;
  
  public:

    Animation();

    Animation(const Animation&);

    virtual ~Animation();

    void addClip(const AnimationClip& clip);

    std::vector<AnimationClip> getClips() const;

    const AnimationClip& getClipAt(const unsigned int&) const;

    unsigned short getClipCount() const;

  };

}

#endif
