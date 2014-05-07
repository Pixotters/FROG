#ifndef FROG_ROUNDCOLLIDER_HPP
#define FROG_ROUNDCOLLIDER_HPP

#include "FROG/Collision/Collider.hpp"
#include "FROG/ComponentHolder.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace frog{

  class RoundCollider : virtual public Collider
  {
  public:
    /// the radius
    float radius;
    /// the bounding box
    sf::Vector2f center;
    /// the gap between origin of parent and origin of the box
    sf::Vector2i gap;


  public:
    RoundCollider(float rad = 1.0f,
                const sf::Vector2i& gap = sf::Vector2i(0,0) );
    virtual ~RoundCollider();
    virtual sf::FloatRect getBoundingBox() const;
    virtual float getXMin() const;
    virtual float getYMin() const;
    virtual float getXMax() const;
    virtual float getYMax() const;
    virtual void update(const ComponentHolder&);
    virtual void resize(float);
    virtual void setGap(const sf::Vector2i&);

  };

}

#endif
