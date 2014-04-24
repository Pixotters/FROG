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

  protected:
    std::map<ID, Animation *> m_animations;
    std::vector<Clip * > m_clips;

  public:
    Spritesheet();
    virtual ~Spritesheet();
    bool loadFromFile(const std::string& file);
    Animation * getAnimation(ID id) const;
    Clip * getClip(const unsigned short&) const;
    void addAnimation(Animation * a, ID id);
    void addClip(Clip * c, const unsigned short&);

  protected:
    void deleteAnimations();
    void deleteClips();
  };

}

#include "FROG/Rendering/Spritesheet.inl"

#endif
