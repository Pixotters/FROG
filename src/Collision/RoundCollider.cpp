#include "FROG/Collision/RoundCollider.hpp"

namespace frog{

  RoundCollider::RoundCollider(float rad,
                               const sf::Vector2i& _gap)
    : Collider(), radius(rad), gap(_gap)
  {
  }

  RoundCollider::~RoundCollider()
  {
  }

  sf::FloatRect RoundCollider::getBoundingRound() const
  {
    sf::FloatRect box;
    box.left = center.x - radius;
    box.top = center.y - radius;
    box.width = radius;
    box.height = radius;

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
    auto t = parent->getComponent<Transform>("TRANSFORM");
    // centering the circle at the origin of the parent
    center = t->getOrigin() + gap;
    auto pos = t->getPosition() - t->getOrigin();
    box.left = pos.x + gap.x;
    box.top = pos.y + gap.y;
  }

  virtual void resize(float newsize)
  {
    radius = newsize;
  }

  virtual void setGap(const sf::Vector2i& newgap)
  {
    gap.x = newgap.x;
    gap.y = newgap.y;
  }

}
