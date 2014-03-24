#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include "CollisionManager.hpp"
#include "Collisionable.hpp"
#include "ActionManager.hpp"

namespace sap {

    class LSAP : virtual public CollisionManager<Collisionable> {

    private:

        /* BEGIN: private classes for LSAP collision manager */

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

        /* END: private classes for LSAP collision manager */

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
         * of collision/separation. Does not affect the EndPoint.value, which 
         * must be updated before calling updateEndPoint.
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

        LSAP (ActionManager * am);

        ~LSAP ();

        /**
         * Create a bounding box attached to a Collisionable and insert its
         * points in xAxis and yAxis (keep it sorted)
         * @param c Object (Collisionable) attached to the new bounding box
         *          to insert in the list
         */
        void addObject(Collisionable * c);

        /**
         * Update Collisionable's EndPoints position in CollisionManger. 
         * Detect collisions and separation and act according to 
         * actionManager. Should be called as soon as an object moves.
         * @param c Object to update
         */
        void updateObject(Collisionable * c);  
  
        /**
         * Remove a bounding box attached to a Collisionable 
         * @param c Object attached to the bounding box to remove
         */
        void removeObject(Collisionable * c);
    };
}
#endif
