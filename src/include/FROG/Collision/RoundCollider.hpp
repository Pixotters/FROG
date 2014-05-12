#ifndef FROG_ROUNDCOLLIDER_HPP
#define FROG_ROUNDCOLLIDER_HPP

#include "FROG/Collision/Collider.hpp"
#include "FROG/ComponentHolder.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>

namespace frog{

  class RoundCollider : virtual public Collider
  {

  public:
    typedef std::shared_ptr<RoundCollider> PTR;

  public:
    /// the radius
    sf::Vector2f radius;
    /// the bounding box
    sf::Vector2f center;
    /// the gap between origin of parent and origin of the box
    sf::Vector2f gap;


  public:
    RoundCollider(const sf::Vector2f& rad = sf::Vector2f(1.0f, 1.0f),
                  const sf::Vector2f& gap = sf::Vector2f(0,0),
                  std::function<void(Collision)> = [](Collision){} );
    virtual ~RoundCollider();
    virtual sf::FloatRect getBoundingBox() const;
    virtual float getXMin() const;
    virtual float getYMin() const;
    virtual float getXMax() const;
    virtual float getYMax() const;
    virtual void update(const ComponentHolder&);
    virtual void resize(const sf::Vector2f&);
    virtual void setGap(const sf::Vector2f&);
    static PTR create(const sf::Vector2f& rad = sf::Vector2f(1,1),
                      const sf::Vector2f& gap = sf::Vector2f(0,0),
                      std::function<void(Collision)> = [](Collision){} );


  };

}

#endif
