#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include <map>
#include <typeinfo>
#include "CollisionManager.hpp"

struct AABB {
    /** min/max
     *  - first is x axis
     *  - second is y axis */
    struct EndPoint * min[2];
    struct EndPoint * max[2];

    size_t typeId; /* Need to use std::type_info::hash_code() */
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

/**
 * Action manager stores actions to perform on collision or separation
 * of two objects depending on their type
 * It also stores default actions to execute if no specific action is
 * defined for two types.
 */
struct ActionManager {

    std::map < std::pair < size_t,size_t >,
               std::pair < std::function < void (void *, void *) >,
                           std::function < void (void *, void *) > > > actions;
 
    std::function < void (void *, void *) >
    onCollision(size_t t1, size_t t2) {
        return this
            ->actions[std::pair<size_t, size_t>(t1,t2)].first;
    }
    
    std::function < void (void *, void *) >
    onSeparation(size_t t1, size_t t2) {
        return this
            ->actions[std::pair<size_t, size_t>(t1,t2)].second;
    }
};

class SAPList : public CollisionManager<struct AABB> {

private:
    /** FIXME: use sentinels */
    struct EndPoint * xAxis;
    struct EndPoint * yAxis;
    struct ActionManager actions;

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
                                      int dim) {
        return (b1.max[dim] <= b2.max[dim] && b1.max[dim] >= b2.min[dim])
            || (b1.min[dim] >= b2.min[dim] && b1.max[dim] <= b2.max[dim]);
    }

    bool collisionCheck(const struct AABB & b1, const struct AABB & b2) {
        return partialCollisionCheck (b1, b2, 0)
            && partialCollisionCheck (b1, b2, 1);
    }

    void updateEndPoint(struct EndPoint * pt) {
        
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
                    this->actions.onCollision
                        (pt->owner->typeId, tmp->owner->typeId)
                        (pt->owner->owner, tmp->owner->owner);
                    }
                } else if (mustRm(pt, tmp)) {
                    this->actions.onSeparation
                        (pt->owner->typeId,tmp->owner->typeId)
                        (pt->owner->owner, tmp->owner->owner);
                }
            }
        };

        /** TODO: use aux to update on x and y axis */

    }
    
public:
    void addObject(const struct AABB &) {}
    void updateObject(const struct AABB &) {}
    void removeObject(const struct AABB &) {}
};

#endif
