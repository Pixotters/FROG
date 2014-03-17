#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include <map>
#include <typeinfo>
#include <climits>
#include "CollisionManager.hpp"

class Collisionable {
public:
    virtual int getXMin() = 0;
    virtual int getYMin() = 0;
    virtual int getXMax() = 0;
    virtual int getYMax() = 0;
    virtual ~Collisionable() {};
};

class SAPList : public CollisionManager<Collisionable> {

    class EndPoint;

    class AABB {
    public:
        /** min/max
         *  - first is x axis
         *  - second is y axis */
        EndPoint * min[2];
        EndPoint * max[2];

        size_t typeId; /* Need to use std::type_info::hash_code() */
        void * owner;

        AABB (int minX, int minY, int maxX, int maxY, size_t t, void * o) :
            typeId(t), owner(o) {
            min[0] = new EndPoint(this, minX, true);
            min[1] = new EndPoint(this, minY, true);
            max[0] = new EndPoint(this, maxX, false);
            max[1] = new EndPoint(this, maxY, false);
        }

    };

    /**
     * TODO:
     * - Optimize merging isMin boolean into another member
     *   (as a flag)
     * - Using doubly-linked list could waste memory but is easier to implement
     *   than arrays.
     * - Implement pair manager
     */
    class EndPoint {
    public:
        AABB * owner;
        int value; //FIXME: use a pointer?
        bool isMin;

        EndPoint * prev;
        EndPoint * next;

        EndPoint (AABB* o,int v,bool m,EndPoint* p=NULL,EndPoint* n=NULL) : 
            owner(o), value(v), isMin(m), prev(p), next(n) {}

        /** When and EndPoint is destroyed, it updates prev and next */
        ~EndPoint () {
            if (this->prev != NULL) {
                this->prev->next = this->next;
            }
            if (this->next != NULL)
                this->next->prev = this->prev;
        }
    };


    /**
     * Action manager stores actions to perform on collision or separation
     * of two objects depending on their type
     * It also stores default actions to execute if no specific action is
     * defined for two types.
     */
    class ActionManager {
    public:
        /**
         * action table stores 2 actions per types couple:
         * - first is onCollision
         * - second is onSeparation
         */
        std::map < std::pair < size_t,size_t >,
                   std::pair < std::function < void (void *, void *) >,
                               std::function < void (void *, void *) > > > 
        actions;


        ActionManager () {}


        /** Add an action to ActionManager
         * @param t1 first object type (hashcode)
         * @param t2 second  object type (hashcode)
         * @param onCollision function to call on collision of t1 and t2
         * @param onSeparation function to call on separation of t1 and t2
         */
        void addAction(size_t t1, size_t t2,
                  std::function <void (void *, void *)> onCollision,
                  std::function <void (void *, void *)> onSeparation) {
            this->actions[std::pair < size_t, size_t > (t1,t2)] =
                std::pair < std::function < void (void *, void *) >,
                            std::function < void (void *, void *) > >
                (onCollision, onSeparation);
        } 
        /**
         * @param t1 type id of first object
         * @param t2 type id of second object
         * @return function to call on t1/t2 collision
         */
        std::function < void (void *, void *) >
        onCollision(size_t t1, size_t t2) {
            return this
                ->actions[std::pair<size_t, size_t>(t1,t2)].first;
        }

        /**
         * @param t1 type id of first object
         * @param t2 type id of second object
         * @return function to call on t1/t2 separation
         */    
        std::function < void (void *, void *) >
        onSeparation(size_t t1, size_t t2) {
            return this
                ->actions[std::pair<size_t, size_t>(t1,t2)].second;
        }
    };


private:

    EndPoint * xAxis;
    EndPoint * yAxis;
    ActionManager actions;

    /** Swap two EndPoint * */
    void swap(EndPoint * p1, EndPoint * p2) {
        p2->next->prev = p1;
        p1->next = p2->next;
        p1->prev->next = p2;
        p1->prev = p2;
        p2->next = p1;
    }

    /** A collision between two AABB on one axis */
    inline bool partialCollisionCheck(const AABB & b1,
                                      const AABB & b2,
                                      int dim) {
        return (b1.max[dim] <= b2.max[dim] && b1.max[dim] >= b2.min[dim])
            || (b1.min[dim] >= b2.min[dim] && b1.max[dim] <= b2.max[dim]);
    }

    /**
     * Check if two AABB collide using 2 axises
     * @see partialCollisionCheck
     */
    bool collisionCheck(const AABB & b1, const AABB & b2) {
        return partialCollisionCheck (b1, b2, 0)
            && partialCollisionCheck (b1, b2, 1);
    }


    /** Create the AABB corresponding to a collisionable object
     * @param c the object used to create the corresponding AABB
     * @return a pointer to freshly heap-allocated AABB 
     */
    AABB * mk_AABB(Collisionable * c) {
        return new AABB(c->getXMin(), c->getYMin(),
                        c->getXMax(), c->getYMax(),
                        typeid(c).hash_code(), (void *) c);
    }


    /** Update EndPoint place and call the appropriate function in case 
     * of collision/separation
     * @param pt the EndPoint to update
     */
    void updateEndPoint(EndPoint * pt) {
        
         auto aux =
            [&pt, this]
            (std::function<EndPoint*(EndPoint*)>succ,
             std::function<bool(int,int)>loop_cond,
             std::function<bool(EndPoint*,EndPoint*)>mustAdd,
             std::function<bool(EndPoint*,EndPoint*)>mustRm) {
            
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

    SAPList () {
        /* not sure about the true/false values */
        xAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        xAxis->next = new EndPoint(NULL, INT_MAX, false, xAxis, NULL);
        yAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        yAxis->next = new EndPoint(NULL, INT_MAX, false, yAxis, NULL);
    }

    ~SAPList () {

        while (xAxis->next != NULL) {
            delete xAxis->next;
        } delete xAxis;

        while (yAxis->next != NULL) {
            delete yAxis->next;
        } delete yAxis;
    }

    void addObject(const Collisionable &) {}
    void updateObject(const Collisionable &) {}
    void removeObject(const Collisionable &) {}
};

#endif
