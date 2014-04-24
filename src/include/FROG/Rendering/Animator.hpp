#ifndef FROG_ANIMATOR_HPP
#define FROG_ANIMATOR_HPP

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Animation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <exception>
#include <map>

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
    std::map< ID, Animation > m_animations;
    sf::Sprite m_sprite;
    ID m_defaultAnim;

  public:

    Animator();

    virtual ~Animator();

    virtual void update(const ComponentHolder& parent);

    void addAnimation(const Animation& a, ID id);

    void playAnimation(ID id, bool loop = false) throw (NoSuchAnimation);
  
    void removeAnimation(ID id);

    ID setDefaultAnimation(ID id) throw (NoSuchAnimation);

  };

}

#include "FROG/Rendering/Animator.inl"

#endif
