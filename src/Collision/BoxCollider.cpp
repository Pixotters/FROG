#include "FROG/Collision/BoxCollider.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  BoxCollider::BoxCollider(const sf::Vector2f& dimensions,
                           const sf::Vector2f& _gap,
                           std::function<void(Collision)> fun )
    : Collider(fun), gap(_gap)
  {
    rectangle.setSize( dimensions );
    rectangle.setOrigin( gap );
  }

  BoxCollider::~BoxCollider()
  {
  }

  sf::FloatRect BoxCollider::getBoundingBox() const
  {
    return rectangle.getGlobalBounds();
  }

  float BoxCollider::getXMin() const
  {
    return rectangle.getGlobalBounds().left;
  }

  float BoxCollider::getYMin() const
  {
    return rectangle.getGlobalBounds().top;
  }

  float BoxCollider::getXMax() const
  {
    auto gb = rectangle.getGlobalBounds();
    return gb.left + gb.width;
  }

  float BoxCollider::getYMax() const
  {
    auto gb = rectangle.getGlobalBounds();
    return gb.top + gb.height;
  }

  void BoxCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // centering the box at the origin of the parent
    /*    auto pos = t->getPosition() - t->getOrigin();
    gap.x *= t->getScale().x;
    gap.x *= t->getScale().y;
    box.left = pos.x + gap.x;
    box.top = pos.y + gap.y;
    box.width = t->getScale().x * dimensions.x;
    box.height = t->getScale().y * dimensions.y;
    */
    rectangle.setOrigin( t->getOrigin() + gap);
    rectangle.setScale( t->getScale() );
    rectangle.setPosition( t->getPosition() );
    rectangle.setRotation( t->getRotation() );
  }

  void BoxCollider::resize(const sf::Vector2f& newsize)
  {
    rectangle.setSize(newsize);
  }

  void BoxCollider::setGap(const sf::Vector2f& newgap)
  {
    gap = newgap;
  }

  BoxCollider::PTR BoxCollider::create(const sf::Vector2f& dimensions,
                                       const sf::Vector2f& gap,
                                       std::function<void(Collision)> fun)
  {
    return PTR(new BoxCollider(dimensions, gap, fun) );
  }

}
