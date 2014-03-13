#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP 1

/** Interface for collision managers */

class CollisionManager <typename AABB> {

    virtual void addObject(const & AABB) = 0;

    /**
     * update object position in list
     * update pair manager
     * do not update EndPoint values
     */
    virtual void updateObject(const & AABB) = 0;

    virtual void removeObject(const & AABB) = 0;


    /** @return pairs of overlapping boxes */
    virtual std::vector<AABB * [2]> getOverlapping() = 0;

}
#endif
