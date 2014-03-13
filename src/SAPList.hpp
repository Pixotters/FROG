#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include "CollisionManager.hpp"

struct AABB {
    /** min/max
     *  - first is x axis
     *  - second is y axis */
    struct EndPoint * min[2];
    struct EndPoint * max[2];
    void * owner;
};

/**
 * TODO:
 * - Optimize merging isMin boolean into another member
 *   (as a flag)
 * - Using doubly-linked list could waste memory but is easier to implement
 *   than arrays.
 * - Implement pair manager
 */
struct EndPoint {
    struct AABB * owner;
    int value;
    bool isMin;

    struct EndPoint * prev;
    struct EndPoint * next;
};

class PairManager {
public:
    void addPair(const struct AABB &, const struct AABB &) {};
    void removePair(const struct AABB &, const struct AABB &) {};
};

class SAP : public CollisionManager<struct AABB> {
   

private:
    /** FIXME: use sentinels */
    struct EndPoint * xAxis;
    struct EndPoint * yAxis;
    PairManager pm;

    void swap(struct EndPoint * p1, struct EndPoint * p2) {
        p2->next->prev = p1;
        p1->next = p2->next;
        p1->prev->next = p2;
        p1->prev = p2;
        p2->next = p1;
    }

    /* check on one axis */
    inline bool partialCollisionCheck(const struct AABB & b1,
                                      const struct AABB & b2,
                                      char dim) {
        return (b1.max[dim] <= b2.max[dim] && b1.max[dim] >= b2.min[dim])
            || (b1.min[dim] >= b2.min[dim] && b1.max[dim] <= b2.max[dim]);
    }

    bool collisionCheck(const struct AABB & b1, const struct AABB & b2) {
        return partialCollisionCheck (b1, b2, 0)
            && partialCollisionCheck (b1, b2, 1);
    }

    void updateEndPoint(struct EndPoint * pt) {
        
        //std::function<void(struct EndPoint * pt)> 
        auto aux =
            [&pt, this]
            (std::function<struct EndPoint*(struct EndPoint*)>succ,
             std::function<bool(int,int)>loop_cond,
             std::function<bool(struct EndPoint*,struct EndPoint*)>mustAdd,
             std::function<bool(struct EndPoint*,struct EndPoint*)>mustRm) {
            
            EndPoint * tmp = succ(pt);
            
            while (loop_cond(tmp->value, pt->value)) {
                this->swap(tmp, pt);
                if (mustAdd(pt, tmp)) {
                    if (this->collisionCheck(*(pt->owner), *(tmp->owner))) {
                        pm.addPair(*(pt->owner), *(tmp->owner));
                    }
                } else if (mustRm(pt, tmp)) {
                    pm.removePair(*(pt->owner), *(tmp->owner));
                }
            }
        };

        /** TODO: use aux to update on x and y axis */

    }
    
public:
    void addObject(const struct AABB &) {}
    void updateObject(const struct AABB &) {}
    void removeObject(const struct AABB &) {}
    int main () {};
};

#endif
