#ifndef FROG_ANIMATION_HPP
#define FROG_ANIMATION_HPP

#include "FROG/Rendering/AnimationClip.hpp"
#include <SFML/Graphics/Texture.hpp>

#include <exception>
#include <sstream>
#include <vector>

namespace frog{

  class Animation
  {

  public:
    class NoSuchAnimClip : virtual public std::exception
    {
      unsigned int id;
    public:
      NoSuchAnimClip(const unsigned int& i)
      : id(i)
      {}

      virtual const char* what() const throw()
      {
        std::ostringstream oss;
        oss << "No such AnimationClip ";
        oss << id;
        oss.flush();
        return oss.str().c_str();
      }
      
    };

  protected:
    std::vector<AnimationClip> m_clips;
  
  public:

    Animation();

    Animation(const Animation&);

    virtual ~Animation();

    void addClip(const AnimationClip& clip);

    std::vector<AnimationClip> getClips() const;

    const AnimationClip& getClipAt(const unsigned int&) const
      throw (NoSuchAnimClip);

    unsigned short getClipCount() const;

  };

}

#endif
