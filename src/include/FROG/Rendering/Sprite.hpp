#ifndef FROG_SPRITE_HPP
#define FROG_SPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/ComponentHolder.hpp"

#include <memory>

namespace frog{

  /*!
   * Sprite allows to display an image easily. 
   */
  class Sprite : virtual public RenderingComponent
  {

  private:
    std::shared_ptr<sf::Sprite> m_sprite;

  public:

    Sprite(const sf::Texture&);

    virtual ~Sprite();

  };

}

#endif
