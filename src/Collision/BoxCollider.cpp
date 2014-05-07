#include "FROG/Collision/BoxCollider.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  BoxCollider::BoxCollider(const sf::Vector2u& dimensions,
                           const sf::Vector2i& _gap)
    : Collider(), gap(_gap)
  {
    box.left = gap.x;
    box.top = gap.y;
    box.width = dimensions.x;
    box.height = dimensions.y;
  }

  BoxCollider::~BoxCollider()
  {
  }

  sf::FloatRect BoxCollider::getBoundingBox() const
  {
    return box;
  }

  float BoxCollider::getXMin() const
  {
    return box.left;
  }

  float BoxCollider::getYMin() const
  {
    return box.top;
  }

  float BoxCollider::getXMax() const
  {
    return box.left + box.width;
  }

  float BoxCollider::getYMax() const
  {
    return box.top + box.height;
  }

  void BoxCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // centering the box at the origin of the parent
    auto pos = t->getPosition() - t->getOrigin();
    box.left = pos.x + gap.x;
    box.top = pos.y + gap.y;
  }

  void BoxCollider::resize(const sf::Vector2u& newsize)
  {
    box.width = newsize.x;
    box.height = newsize.y;
  }

  void BoxCollider::setGap(const sf::Vector2i& newgap)
  {
    gap.x = newgap.x;
    gap.y = newgap.y;
  }

}
