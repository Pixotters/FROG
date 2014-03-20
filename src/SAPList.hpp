#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include <map>
#include <typeinfo>
#include <climits>
#include <iostream>
#include "CollisionManager.hpp"

class ActionManager;
class Collisionable;
class SAPList;

class Collisionable {

protected:
    /* (void *) because AABB type is hidden */
    void * boundingBox;

public:
    /**
     * @return a pointer to Collisionable's bouding box (it needs cast).
     */
    void * getBoundingBox() { return boundingBox; }

    /**
     * Change the boundingBox of a Collisionable
     * @param b new bounding box
     */
    void setBoundingBox(void * b) { boundingBox = b; }

    /** @return the smallest value of a Collisionable on X axis */
    virtual int getXMin() = 0;

    /** @return the smallest value of a Collisionable on Y axis */
    virtual int getYMin() = 0;

    /** @return the greatest value of a Collisionable on X axis */
    virtual int getXMax() = 0;

    /** @return the greatest value of a Collisionable on Y axis */
    virtual int getYMax() = 0;

    virtual ~Collisionable() {};
};

class ActionManager {

public:
    /**
     * Function to call on collision
     * @param o1 first object which collide
     * @param o2 second object which collide
     */
    virtual void onCollision(Collisionable * o1, Collisionable * o2) = 0;

    /**
     * @param o1 first object which do not collide
     * @param o2 second object which do not collide
     */
    virtual void onSeparation(Collisionable * o1, Collisionable * o2) = 0;

    virtual ~ActionManager() {};

};

class SAPList : virtual public CollisionManager<Collisionable> {

private:

    /* BEGIN: private classes for SAPList collision manager */

    class AABB;

    class EndPoint {

        /**
         * TODO:
         * - Optimize merging isMin boolean into another member
         *   (as a flag)
         * - Using doubly-linked list could waste memory but is easier to 
         *   implement than arrays.
         */

    public:

        AABB * owner;
        /** Value used to sort EndPoint list */
        int value;

        /** Flag to indicate if this EndPoint is minimum of a AABB or not */
        bool isMin;

        /** Previous EndPoint in the list */
        EndPoint * prev;

        /** Next EndPoint in the list */
        EndPoint * next;

        EndPoint (AABB* o,int v,bool m,EndPoint* p=NULL,EndPoint* n=NULL) : 
            owner(o), value(v), isMin(m), prev(p), next(n) {}
    
        /** When and EndPoint is destroyed, it updates prev and next */
        ~EndPoint () {
            if (this->prev != NULL) {
                this->prev->next = this->next;
            }
            if (this->next != NULL) {
                this->next->prev = this->prev;
            }
        }
    };
    
    class AABB {

    public:

        /** First minimum EndPoint is on x axis, second one is on y */
        EndPoint * min[2];

        /** Second minimum EndPoint is on x axis, second one is on y */
        EndPoint * max[2];

        /** Object the box is attached to */
        Collisionable * owner;

        /**
         * Create the AABB corresponding to a collisionable object
         * @param c the object used to create the corresponding AABB
         */
        AABB(Collisionable * c) : owner(c) {
            min[0] = new EndPoint(this, c->getXMin(), true);
            min[1] = new EndPoint(this, c->getYMin(), true);
            max[0] = new EndPoint(this, c->getXMax(), false);
            max[1] = new EndPoint(this, c->getYMax(), false);
            c->setBoundingBox(this);
        }

        /**
         * When a AABB is destroyed, its owner bounding box is set to NULL
         */
        ~AABB () { 
            delete min[0];
            delete min[1];
            delete max[0];
            delete max[1];
            if (owner) {
                //   owner->setBoundingBox(NULL); <- segfault in unit tests.
            }
        }


        /**
         * Update EndPoints values according to information provided by
         * owner and Collisionable API
         */
        void updateEPValues() {
            min[0]->value = owner->getXMin();
            min[1]->value = owner->getYMin();
            max[0]->value = owner->getXMax();
            max[1]->value = owner->getYMax();
        }

    };

    /* END: private classes for SAPList collision manager */

private:

    /** First EndPoint on xAxis (not a real point, but a sentinel)*/
    EndPoint * xAxis;

    /** Second EndPoint on xAxis (not a real point, but a sentinel)*/
    EndPoint * yAxis;

    /** Action manager used on collision/separation */
    ActionManager * actionManager;

    /** Swap two EndPoint.
     * **p2 has to be the direct next EndPoint after p1**
     * @param p1 first EndPoint
     * @param p2 second EndPoint
     */
    void swap(EndPoint * p1, EndPoint * p2) {
        if (p2->next != NULL) p2->next->prev = p1;
        if (p1->prev != NULL) p1->prev->next = p2;
        p1->next = p2->next;
        p2->next = p1;  
        p2->prev = p1->prev;
        p1->prev = p2;            
    }

    /**
     * A collision between two AABB on one axis
     * no collision on equality (>/<)
     */
    inline bool partialCollisionCheck(const AABB & a,
                                      const AABB & b,
                                      int dim) {
        return !(a.min[dim]->value > b.max[dim]->value
                 || a.max[dim]->value < b.min[dim]->value);
    }

    /**
     * Check if two AABB collide using 2 axises
     * @see partialCollisionCheck
     */
    bool collisionCheck(const AABB & b1, const AABB & b2) {
        return partialCollisionCheck (b1, b2, 0)
            && partialCollisionCheck (b1, b2, 1);
    }


    /** Update EndPoint place and call the appropriate function in case 
     * of collision/separation. Does not affect the EndPoint.value, which must 
     * be updated before calling updateEndPoint.
     * @param pt the EndPoint to update
     */
    void updateAxis(EndPoint * min, EndPoint * max) {
        
        auto update =
            [this]
            (EndPoint * pt,
             std::function<EndPoint*(EndPoint*)>succ,
             std::function<bool(EndPoint*pt,EndPoint*succ)>loop_cond,
             std::function<void(EndPoint*pt,EndPoint*succ)>swap_fun,
             std::function<bool(EndPoint*pt,EndPoint*succ)>doCollide,
             std::function<bool(EndPoint*pt,EndPoint*succ)>doSeparate) {
          
            EndPoint * tmp = succ(pt);
            if (!loop_cond(pt, tmp))
                { return false; }

            do {
                swap_fun(pt, tmp);

                if (doCollide(pt, tmp)) {
                    if (this->collisionCheck(*(pt->owner), *(tmp->owner))) {
                        this->actionManager->onCollision(pt->owner->owner,
                                                         tmp->owner->owner);
                    }
                } else if (doSeparate(pt, tmp)) {
                    this->actionManager->onSeparation(pt->owner->owner,
                                                      tmp->owner->owner);
                }

                tmp = succ(pt);
            } while (loop_cond(pt, tmp));
            
            return true;
        };

        /* No collision detected on equality (<=/>=). */

        auto prev = [](EndPoint *p)
            { return p->prev;};
        auto prev_cond = [](EndPoint * pt, EndPoint * succ)
            { return pt->value < succ->value; };
        auto prev_swap = [this](EndPoint * pt, EndPoint * succ)
            { swap(succ, pt); };
        auto prev_col = [](EndPoint *pt, EndPoint *succ)
            { return pt->isMin && !succ->isMin; };
        auto prev_sep = [](EndPoint *pt, EndPoint *succ)
            { return !pt->isMin && succ->isMin; };
                     
        auto next = [](EndPoint *p)
            { return p->next; };
        auto next_cond = [](EndPoint * pt, EndPoint * succ)
            { return pt->value > succ->value; };
        auto next_swap = [this](EndPoint * pt, EndPoint * succ)
            { swap(pt, succ); };
        auto next_col = [](EndPoint *pt, EndPoint *succ)
            { return !pt->isMin && succ->isMin; };
        auto next_sep = [](EndPoint *pt, EndPoint *succ)
            { return pt->isMin && !succ->isMin; };
        
        /* BINOR force update and allow to use a boolean test */
        if(!(update(max, next, next_cond, next_swap, next_col, next_sep) |
             update(min, next, next_cond, next_swap, next_col, next_sep))) {
               update(min, prev, prev_cond, prev_swap, prev_col, prev_sep);
               update(max, prev, prev_cond, prev_swap, prev_col, prev_sep);
           }

    }
    
public:

    SAPList (ActionManager * am) {
        this->actionManager = am;
        /* not sure about the true/false values */
        xAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        xAxis->next = new EndPoint(NULL, INT_MAX, false, xAxis, NULL);
        yAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        yAxis->next = new EndPoint(NULL, INT_MAX, false, yAxis, NULL);
    }

    ~SAPList () {
        
        /* delete all AABB will delete EndPoints */
        while (xAxis->next != NULL && xAxis->next->owner != NULL) {
            delete xAxis->next->owner;
        }
        /* delete all sentinels */
        delete xAxis->next;
        delete xAxis;
        delete yAxis->next;
        delete yAxis;
    }


    /**
     * Create a bounding box attached to a Collisionable and insert its
     * points in xAxis and yAxis (keep it sorted)
     * @param c Object (Collisionable) attached to the new bounding box
     *          to insert in the list
     */
    void addObject(Collisionable * c) {

        AABB * aabb = new AABB(c);

        aabb->min[0]->next = aabb->max[0];
        aabb->max[0]->prev = aabb->min[0];
        aabb->min[0]->prev = xAxis;
        aabb->max[0]->next = xAxis->next;
        xAxis->next->prev = aabb->max[0];
        xAxis->next = aabb->min[0];

        aabb->min[1]->next = aabb->max[1];
        aabb->max[1]->prev = aabb->min[1];
        aabb->min[1]->prev = yAxis;
        aabb->max[1]->next = yAxis->next;
        yAxis->next->prev = aabb->max[1];
        yAxis->next = aabb->min[1];

        updateObject(c);
    }


    /**
     * Update Collisionable's EndPoints position in CollisionManger. Detect 
     * collisions and separation and act according to actionManager. Should 
     * be called as soon as an object moves.
     * @param c Object to update
     */
    void updateObject(Collisionable * c) {
        AABB * aabb = static_cast<AABB *>(c->getBoundingBox());
        aabb->updateEPValues();
        updateAxis(aabb->min[0], aabb->max[0]);
        updateAxis(aabb->min[1], aabb->max[1]);
    }
  
  
    /**
     * Remove a bounding box attached to a Collisionable 
     * @param c Object attached to the bounding box to remove
     */
    void removeObject(Collisionable * c) {
        delete static_cast<AABB *>(c->getBoundingBox());
    }
};

#endif
