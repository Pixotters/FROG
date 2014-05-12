#include "FROG/Collision/RoundCollider.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  RoundCollider::RoundCollider(const sf::Vector2f& rad,
                               const sf::Vector2f& _gap,
                               std::function<void(Collision)> fun )
    : Collider(fun), radius(rad), gap(_gap)
  {
  }

  RoundCollider::~RoundCollider()
  {
  }

  sf::FloatRect RoundCollider::getBoundingBox() const
  {
    sf::FloatRect box;
    box.left = center.x - radius.x;
    box.top = center.y - radius.y;
    box.width = radius.x;
    box.height = radius.y;
    return box;
  }

  float RoundCollider::getXMin() const
  {
    return center.x - radius.x;
  }

  float RoundCollider::getYMin() const
  {
    return center.y - radius.y;
  }

  float RoundCollider::getXMax() const
  {
    return center.x + radius.x;
  }

  float RoundCollider::getYMax() const
  {
    return center.y + radius.y;
  }

  void RoundCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // centering the circle at the origin of the parent
    radius.x *= t->getScale().x;
    radius.y *= t->getScale().y;
    center = t->getOrigin() + gap;
  }

  void RoundCollider::resize(const sf::Vector2f& newsize)
  {
    radius = newsize;
  }

  void RoundCollider::setGap(const sf::Vector2f& newgap)
  {
    gap.x = newgap.x;
    gap.y = newgap.y;
  }

  RoundCollider::PTR RoundCollider::create(const sf::Vector2f& rad,
                                           const sf::Vector2f& gap,
                                           std::function<void(Collision)> fun)
  {
    return PTR(new RoundCollider(rad, gap, fun) );
  }


}
