#ifndef FROG_RENDERING_SPRITESHEET_HPP
#define FROG_RENDERING_SPRITESHEET_HPP

#include "FROG/Rendering/Animation.hpp"
#include "FROG/Rendering/Clip.hpp"

#include <map>
#include <string>
#include <vector>
#include <iostream> // delete

namespace frog{

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
    const Animation& getAnimation(ID id) const;
    const Clip& getClip(const unsigned short&) const;
    void addAnimation(const Animation& a, ID id);
    void addClip(const Clip& c, const unsigned short&);
    //TODO remove
    unsigned short getSize() const
    {
      std::cerr << "SPRITESHEET : Spritesheet "<<this<<" getting size of "<<&m_clips<<std::endl;
      return m_clips.size();
    }

  protected:
    void deleteAnimations();
    void deleteClips();
  };

}

#include "FROG/Rendering/Spritesheet.inl"

#endif
