#ifndef FROG_SPRITE_HPP
#define FROG_SPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <memory>

namespace frog{

  /*!
   * Sprite allows to display an image easily. 
   */
  class Sprite : virtual public RenderingComponent
  {

  public:
    typedef std::shared_ptr<Sprite> PTR;

  public:
    std::shared_ptr<sf::Sprite> image;

  public:

    Sprite(const sf::Texture&);
    Sprite(const sf::Texture&, const sf::IntRect&);
    virtual ~Sprite();
    void setTexture(const sf::Texture&);
    void setClip(const sf::IntRect&);
    static PTR create(const sf::Texture&);
    static PTR create(const sf::Texture&, const sf::IntRect&);

  };

}

#endif
