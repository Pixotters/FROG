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

     /*!
       * @brief Places the Sprite to render at the good place. 
       * @details Places the sprite at the position of its parent, 
       * so the parent need a Transform component. It also takes its rotation 
       * and scale.
       * @param parent ComponentHolder holding position, rotation and scale
       */
    void update(const ComponentHolder& parent);

  };

}

#endif
