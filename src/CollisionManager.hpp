#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP 1

/** Interface for collision managers */

template <typename AABB> class CollisionManager  {

    virtual void addObject(const AABB &) = 0;

    virtual void updateObject(const AABB &) = 0;

    virtual void removeObject(const AABB &) = 0;

};

#endif
