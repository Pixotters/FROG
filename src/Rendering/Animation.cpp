#include "FROG/Rendering/Animation.hpp"

namespace frog{

  Animation::Animation(sf::Texture& tex)
    : m_spritesheet(tex)
  {

  }

  Animation::~Animation()
  {

  }

  void Animation::addClip(Clip * c)
  {
    m_clips.push_back(c);
  }

  void Animation::removeClip(Clip * c)
  {
    m_clips.remove(c);
  }

  std::list<Clip> getClipList() const
  {
    return m_clips;
  }

}
