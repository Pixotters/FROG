#ifndef FROG_BOXCOLLIDER_HPP
#define FROG_BOXCOLLIDER_HPP

#include "FROG/Collision/Collider.hpp"

namespace frog{

  class BoxCollider : virtual public Collider
  {

  protected:
    /// the bounding box
    sf::FloatRect box;
    /// the gap between origin of parent and origin of the box
    sf::Vector2i gap;

  public:
    BoxCollider(const sf::Vector2u& dimensions = sf::Vector2u(1,1),
                const sf::Vector2i& gap = sf::Vector2u(0,0));
    virtual ~BoxCollider();
    virtual sf::FloatRect getBoundingBox() const;
    virtual float getXMin() const;
    virtual float getYMin() const;
    virtual float getXMax() const;
    virtual float getYMax() const;
    virtual void update(const ComponentHolder&);
    virtual void resize(const sf::Vector2u&);
    virtual void setGap(const sf::Vector2i&);

  };

}

#endif
