#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP 1

#include <list>
#include "Collisionable.hpp"

/**
 * The action manager is the interface of objects needed by SAPList.
 * This class handle objects collisions and separations
 */

namespace sap {

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

    class DefaultActionManager : virtual public ActionManager {

        typedef std::pair<Collisionable *, Collisionable *> pair;

    protected:
        std::list < pair > colliding;

    public:

        std::list < pair > getColliding () { return colliding; }

        virtual void onCollision(Collisionable * o1, Collisionable * o2) {
            colliding.push_front(pair(o1, o2));
        }

        virtual void onSeparation(Collisionable * o1, Collisionable * o2) {
            colliding.remove(pair(o1, o2));
        }

        virtual ~DefaultActionManager() {};

    };

}
#endif
