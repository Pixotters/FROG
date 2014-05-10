#ifndef FROG_AABB_HPP
#define FROG_AABB_HPP

#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/EndPoint.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <memory>

namespace frog{

  struct AABB {

  public:

    /** First minimum EndPoint is on x axis, second one is on y */
    EndPoint * min[2];

    /** Second minimum EndPoint is on x axis, second one is on y */
    EndPoint * max[2];

    /** Object the box is attached to */
    std::shared_ptr<Collider> owner;

    /**
     * Create the AABB corresponding to a collisionable object
     * @param c the object used to create the corresponding AABB
     */
    AABB(std::shared_ptr<Collider> c);

    virtual ~AABB ();

    /**
     * Update EndPoints values according to information provided by
     * owner and Collisionable API
     */
    void updateEPValues();

  };
}

#endif