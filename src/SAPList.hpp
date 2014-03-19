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
    void * getBoundingBox() { return boundingBox; }
    void setBoundingBox(void * b) { boundingBox = b; }
    virtual int getXMin() = 0;
    virtual int getYMin() = 0;
    virtual int getXMax() = 0;
    virtual int getYMax() = 0;
    virtual ~Collisionable() {};
};

class ActionManager {

public:
    virtual void onCollision(Collisionable * o1, Collisionable * o2) = 0;
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
         * - Using doubly-linked list could waste memory but is easier to implement
         *   than arrays.
         * - Implement pair manager
         */

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
            /*
            if (this->prev != NULL) {
                this->prev->next = this->next;
            }
            if (this->next != NULL)
                this->next->prev = this->prev;
            */
        }
    };
    
    class AABB {

    public:
        EndPoint * min[2]; /* x/y */
        EndPoint * max[2]; /* x/y */

        Collisionable * owner;

        AABB (int minX, int minY, int maxX, int maxY, Collisionable * o) :
            owner(o) {
            min[0] = new EndPoint(this, minX, true);
            min[1] = new EndPoint(this, minY, true);
            max[0] = new EndPoint(this, maxX, false);
            max[1] = new EndPoint(this, maxY, false);
        }
    };

    /* END: private classes for SAPList collision manager */

private:

    EndPoint * xAxis;
    EndPoint * yAxis;
    ActionManager * actionManager;

    /** Swap two EndPoint.
     * PRECONDITION: p1 is*/
    void swap(EndPoint * p1, EndPoint * p2) {
        if (p2->next != NULL) p2->next->prev = p1;
        if (p1->prev != NULL) p1->prev->next = p2;
        p1->next = p2->next;
        p2->next = p1;  
        p2->prev = p1->prev;
        p1->prev = p2;            
    }

    /** A collision between two AABB on one axis
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


    /** Create the AABB corresponding to a collisionable object
     * @param c the object used to create the corresponding AABB
     * @return a pointer to freshly heap-allocated AABB 
     */
    AABB * mk_AABB(Collisionable * c) {
        return new AABB(c->getXMin(), c->getYMin(),
                        c->getXMax(), c->getYMax(),
                        c);
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
        
        /* first BINOR force update */
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
        /*
        while (xAxis->next != NULL) {
            delete xAxis->next;
        } delete xAxis;

        while (yAxis->next != NULL) {
            delete yAxis->next;
        } delete yAxis;
        */
    }

    void addObject(Collisionable * c) {

        /* create couple and insert after sentinel */

        AABB * aabb = this->mk_AABB(c);
        c->setBoundingBox(aabb);

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

    void updateObject(Collisionable * c) {
        AABB * aabb = static_cast<AABB *>(c->getBoundingBox());
        updateAxis(aabb->min[0], aabb->max[0]);
        updateAxis(aabb->min[1], aabb->max[1]);
    }

    void removeObject(Collisionable * c) {
    }
};

#endif

/*
  if (mustAdd(pt, tmp)) {
  if (this->collisionCheck(*(pt->owner), *(tmp->owner))) {
  this->actionManager->onCollision(pt->owner->owner,
  tmp->owner->owner);
  }
  } else if (mustRm(pt, tmp)) {
  this->actionManager->onSeparation(pt->owner->owner,
  tmp->owner->owner);
  }
*/
