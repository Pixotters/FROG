#ifndef FROG_ANIMATOR_HPP
#define FROG_ANIMATOR_HPP

#include "FROG/ComponentHolder.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Rendering/Animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <exception>
#include <map>
#include <string>

namespace frog{

  template <typename ID>
  class Animator : virtual public RenderingComponent
  {

  public:
    class NoSuchAnimation : virtual public std::exception{

      virtual const char* what() const throw()
      {        
        return "Couldn't play missing animation.";
      }

    };

  protected:
    Spritesheet& m_spritesheet;
    sf::Texture& m_texture;

  public:

    Animator(Spritesheet&, sf::Texture&);

    virtual ~Animator();

    virtual void update(const ComponentHolder& parent);

    void playAnimation(ID id, bool loop = false) throw (NoSuchAnimation);
  
    ID setDefaultAnimation(ID id) throw (NoSuchAnimation);

    void changeTexture(sf::Texture& );

  };

}

#include "FROG/Rendering/Animator.inl"

#endif
