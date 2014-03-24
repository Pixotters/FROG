#include <map>
#include <climits>

#include "LSAP.hpp"

namespace sap {

    LSAP::LSAP (ActionManager * am) {
        this->actionManager = am;
        /* not sure about the true/false values */
        xAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        xAxis->next = new EndPoint(NULL, INT_MAX, false, xAxis, NULL);
        yAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
        yAxis->next = new EndPoint(NULL, INT_MAX, false, yAxis, NULL);
    }

    LSAP::~LSAP () {
        
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
    void LSAP::addObject(Collisionable * c) {

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
    void LSAP::updateObject(Collisionable * c) {
        AABB * aabb = static_cast<AABB *>(c->getBoundingBox());
        aabb->updateEPValues();
        updateAxis(aabb->min[0], aabb->max[0]);
        updateAxis(aabb->min[1], aabb->max[1]);
    }
  
  
    /**
     * Remove a bounding box attached to a Collisionable 
     * @param c Object attached to the bounding box to remove
     */
    void LSAP::removeObject(Collisionable * c) {
        delete static_cast<AABB *>(c->getBoundingBox());
    }


}
