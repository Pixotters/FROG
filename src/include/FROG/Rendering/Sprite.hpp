#ifndef FROG_SPRITE_HPP
#define FROG_SPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/ComponentHolder.hpp"

namespace frog{

  class Sprite : virtual public render::RenderingComponent
  {

  private:
    sf::Sprite m_sprite;

  public:

    Sprite(const sf::Texture&);

    virtual ~Sprite();

    virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;

    void update(const ComponentHolder& parent);

  };

}

#endif
