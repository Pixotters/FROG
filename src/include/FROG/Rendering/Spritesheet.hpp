#ifndef FROG_RENDERING_SPRITESHEET_HPP
#define FROG_RENDERING_SPRITESHEET_HPP

#include <string>

namespace frog{

  template <typename ID>
  class Spritesheet
  {

  protected:
    sf::Texture * m_texture;
    std::map<ID, Animation *> m_animations;
    std::vector<Clip * > m_clips;

  public:
    Spritesheet();
    virtual ~Spritesheet();
    bool loadFromFile(const string& file);
    Animation * getAnimation(ID id) const;
    void addAnimation(Animation * a, ID id);
    void addClip(Clip * c);

  protected:
    void deleteAnimations();
    void deleteClips();
  };

}

#include "FROG/Rendering/Spritesheet.inl"

#endif
