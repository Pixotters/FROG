#ifndef FROG_RENDERING_SPRITESHEET_HPP
#define FROG_RENDERING_SPRITESHEET_HPP

#include "FROG/Rendering/Animation.hpp"
#include "FROG/Rendering/Clip.hpp"

#include <exception>
#include <map>
#include <string>
#include <vector>

namespace frog{

  class NoSuchAnimation : virtual public std::exception{
    virtual const char* what() const throw()
    {        
      return "Couldn't play missing animation.";
    }
  };
  class NoSuchClip : virtual public std::exception{
    virtual const char* what() const throw()
    {        
      return "Couldn't refer to missing Clip.";
    }
  };


  template <typename ID>
  class Spritesheet
  {

  private:
    std::map<ID, Animation> m_animations;
    std::vector<Clip> m_clips;

  public:
    Spritesheet();
    Spritesheet(const Spritesheet&);
    virtual ~Spritesheet();
    bool loadFromFile(const std::string& file);
    const Animation& getAnimation(ID id) const throw(NoSuchAnimation);
    const Clip& getClip(const unsigned short&) const throw(NoSuchClip);
    void addAnimation(const Animation& a, ID id);
    void addClip(const Clip& c, const unsigned short&);

  protected:
    void deleteAnimations();
    void deleteClips();
  };

}

#include "FROG/Rendering/Spritesheet.inl"

#endif
