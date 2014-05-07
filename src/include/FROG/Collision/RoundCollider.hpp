#ifndef FROG_ROUNDCOLLIDER_HPP
#define FROG_ROUNDCOLLIDER_HPP

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
                const sf::Vector2i& gap = sf::Vector2u(0,0) );
    virtual ~RoundCollider();
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
