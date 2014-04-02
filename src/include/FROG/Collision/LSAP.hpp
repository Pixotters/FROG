#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

#include <functional>
#include "FROG/Collision/CollisionManager.hpp"
#include "FROG/Collision/Collisionable.hpp"
#include "FROG/Collision/ActionManager.hpp"

namespace sap {

    class LSAP : virtual public CollisionManager<Collisionable> {

        /**
         * Sweep And Prune engine, implemented using doubly linked lists
         * **Limitation:** if an object moves too fast, LSAP may miss
         * a collision.
         */


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

            EndPoint (AABB* o,int v,bool m,EndPoint* p=NULL,EndPoint* n=NULL);
    
            /** When and EndPoint is destroyed, it updates prev and next */
            ~EndPoint ();
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
            AABB(Collisionable * c);

            ~AABB ();

            /**
             * Update EndPoints values according to information provided by
             * owner and Collisionable API
             */
            void updateEPValues();

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
        void swap(EndPoint * p1, EndPoint * p2);

        /**
         * A collision between two AABB on one axis
         * no collision on equality (>/<)
         */
        bool partialCollisionCheck(const AABB & a, const AABB & b, int dim);

        /**
         * Check if two AABB collide using 2 axises
         * @see partialCollisionCheck
         */
        bool collisionCheck(const AABB & b1, const AABB & b2);

        /** Update EndPoint place and call the appropriate function in case 
         * of collision/separation. Does not affect the EndPoint.value, which 
         * must be updated before calling updateEndPoint.
         * @param pt the EndPoint to update
         */
        void updateAxis(EndPoint * min, EndPoint * max);
    
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
