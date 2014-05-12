#include "FROG/Collision/RoundCollider.hpp"
#include "FROG/Transform.hpp"

namespace frog{

  RoundCollider::RoundCollider(float rad,
                               const sf::Vector2f& _gap,
                               std::function<void(Collision)> fun )
    : Collider(fun), gap(_gap)
  {
    circle.setRadius(rad);
    circle.setOrigin(gap);
  }

  RoundCollider::~RoundCollider()
  {
  }

  sf::FloatRect RoundCollider::getBoundingBox() const
  {
    return circle.getGlobalBounds();
  }

  float RoundCollider::getXMin() const
  {
    return circle.getGlobalBounds().left;
  }

  float RoundCollider::getYMin() const
  {
    return circle.getGlobalBounds().top;
  }

  float RoundCollider::getXMax() const
  {
    auto gb = circle.getGlobalBounds();
    return gb.left + gb.width;
  }

  float RoundCollider::getYMax() const
  {
    auto gb = circle.getGlobalBounds();
    return gb.top + gb.height;
  }

  void RoundCollider::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    // centering the circle at the origin of the parent
    circle.setOrigin( t->getOrigin() + gap );
    circle.setScale( t->getScale() );
    circle.setPosition( t->getPosition() );
    circle.setRotation( t->getRotation() );
  }

  void RoundCollider::resize(float newrad)
  {
    circle.setRadius(newrad);
  }

  void RoundCollider::setGap(const sf::Vector2f& newgap)
  {
    gap = newgap;
  }

  RoundCollider::PTR RoundCollider::create(float rad,
                                           const sf::Vector2f& gap,
                                           std::function<void(Collision)> fun)
  {
    return PTR(new RoundCollider(rad, gap, fun) );
  }


}
