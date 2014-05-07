#include "FROG/Collision/RoundCollider.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  RoundCollider::RoundCollider(float rad,
                               const sf::Vector2i& _gap,
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
    box.left = center.x - radius;
    box.top = center.y - radius;
    box.width = radius;
    box.height = radius;
    return box;
  }

  float RoundCollider::getXMin() const
  {
    return center.x - radius;
  }

  float RoundCollider::getYMin() const
  {
    return center.y - radius;
  }

  float RoundCollider::getXMax() const
  {
    return center.x + radius;
  }

  float RoundCollider::getYMax() const
  {
    return center.y + radius;
  }

  void RoundCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // centering the circle at the origin of the parent
    center = t->getOrigin() + ( static_cast<sf::Vector2f>(gap) );
  }

  void RoundCollider::resize(float newsize)
  {
    radius = newsize;
  }

  void RoundCollider::setGap(const sf::Vector2i& newgap)
  {
    gap.x = newgap.x;
    gap.y = newgap.y;
  }

}
