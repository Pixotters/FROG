#ifndef FROG_ROUNDCOLLIDER_HPP
#define FROG_ROUNDCOLLIDER_HPP

#include "FROG/Collision/Collider.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{

  class RoundCollider : virtual public Collider
  {

  public:
    typedef std::shared_ptr<RoundCollider> PTR;

  public:
    /// the underlying circle
    sf::CircleShape circle;
    /// the gap between origin of parent and origin of the box
    sf::Vector2f gap;


  public:
    RoundCollider(float rad = 1.0f,
                  const sf::Vector2f& gap = sf::Vector2f(0,0),
                  std::function<void(Collision)> = [](Collision){} );
    virtual ~RoundCollider();
    virtual sf::FloatRect getBoundingBox() const;
    virtual float getXMin() const;
    virtual float getYMin() const;
    virtual float getXMax() const;
    virtual float getYMax() const;
    virtual void update(const ComponentHolder&);
    virtual void resize(float);
    virtual void setGap(const sf::Vector2f&);
    static PTR create(float rad = 1.0f,
                      const sf::Vector2f& gap = sf::Vector2f(0,0),
                      std::function<void(Collision)> = [](Collision){} );


  };

}

#endif
