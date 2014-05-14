#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/AnimationClip.hpp"

#include <vector>

namespace frog{

  /*!
   * Animation is a list of AnimationClips displayed one after the other in 
   * order to simulate movement. 
   */
  class Animation
  {

  protected:
    std::vector<AnimationClip> m_clips;
  
  public:

    Animation();

    Animation(const Animation&);

    virtual ~Animation();

    /*!
     * @brief Adds a clip at the end of the current animation. 
     * @param clip AnimationClip to add.
     */
    void addClip(const AnimationClip& clip);

    std::vector<AnimationClip> getClips() const;

    /*!
     * @brief Return an AnimationClip at the given position. 
     * @details Throws exception "NoSuchAnimClip" if the given integer does not 
     * match an existing animation. 
     * @param i Index of the AnimationClip to get.
     * @return AnimationClip at position i.
     */
    const AnimationClip& getClipAt(unsigned int i) const;

    /*!
     * @brief Returns the number of clips the animation is made of.
     * @return Size of the animation (in number of contained AnimationClips).
     */
    unsigned short getClipCount() const;

  };

}

#endif
