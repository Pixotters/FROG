#ifndef FROG_ANIMATOR_HPP
#define FROG_ANIMATOR_HPP

#include "FROG/ComponentHolder.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Rendering/Animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <exception>
#include <map>
#include <string>
#include <iostream> // TODO remove

namespace frog{

  template <typename ID>
  class Animator : virtual public render::RenderingComponent{

  public:
    class NoSuchAnimation : virtual public std::exception{

      virtual const char* what() const throw()
      {        
        return "Couldn't play missing animation.";
      }

    };

  protected:
    Spritesheet<ID> * m_spritesheet;
    sf::Texture& m_texture;
    sf::Sprite m_sprite;
    Animation * m_defaultAnimation;
    unsigned short m_frameKey;
    bool m_loop;
    Animation * m_played;

  public:

    Animator(Spritesheet<ID> *, sf::Texture&);

    virtual ~Animator();

    virtual void update(const ComponentHolder& parent);

    virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;

    void playAnimation(ID id, bool loop = false) throw (NoSuchAnimation);

    void playAnimation(Animation * a, bool loop = false) throw (NoSuchAnimation);
  
    Animation * setDefaultAnimation(ID id) throw (NoSuchAnimation);

    void changeTexture(sf::Texture& );

    void changeSpritesheet(Spritesheet<ID> * );

  };

}

#include "FROG/Rendering/Animator.inl"

#endif
