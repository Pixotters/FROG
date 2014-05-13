#ifndef FROG_COLLIDER_HPP
#define FROG_COLLIDER_HPP

#include "FROG/Core/Component.hpp"
#include "FROG/Collision/Collision.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace frog{

  /**
   * Collider is the base class for colliders and has to be implemented by
   * all objects meant to be added to Sweep And Prune collision manager.
   */
  class Collider : virtual public Component
  {

  public:

    std::function<void(Collision)> script;

    Collider(std::function<void(Collision)> = [](Collision){} );

    virtual ~Collider();

    /**
     * @brief Returns the smallest rectangle containing the collider.
     * @details Rectangles coordinates at based on the window it is in
     * @return A sf::FloatRect representing bounding rectangle of the collider.
     */
    virtual sf::FloatRect getBoundingBox() const = 0;

    /** @return the smallest value of a Collider on X axis */
    virtual float getXMin() const = 0;

    /** @return the smallest value of a Collider on Y axis */
    virtual float getYMin() const = 0;

    /** @return the greatest value of a Collider on X axis */
    virtual float getXMax() const = 0;

    /** @return the greatest value of a Collider on Y axis */
    virtual float getYMax() const = 0;

    virtual void update(const ComponentHolder&) = 0;

    void setScript(std::function<void(Collision)>);

    /*
     * @brief Function to trigger when this collider collides with another
     */
    void onCollision(const Collision&);

  };
}

#endif
