#ifndef COLLISIONABLE_HPP
#define COLLISIONABLE_HPP 1

/**
 * SAPCollisionable is the interface that **MUST** be implemented by
 * all objects meant to be added to Sweep And Prune collision manager.
 */
namespace sap {
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
        virtual int getXMin() const = 0;

        /** @return the smallest value of a Collisionable on Y axis */
        virtual int getYMin() const = 0;

        /** @return the greatest value of a Collisionable on X axis */
        virtual int getXMax() const = 0;

        /** @return the greatest value of a Collisionable on Y axis */
        virtual int getYMax() const = 0;

        virtual ~Collisionable() {};
    };
}

#endif
