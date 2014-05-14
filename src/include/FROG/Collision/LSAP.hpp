#ifndef FROG_LSAP_HPP
#define FROG_LSAP_HPP 1

#include <map>
#include <memory>
#include "FROG/Core/GameObject.hpp"
#include "FROG/Collision/CollisionManager.hpp"
#include "FROG/Collision/Collision.hpp"
#include "FROG/Collision/AABB.hpp"
#include "FROG/Collision/EndPoint.hpp"

namespace frog {

  class LSAP : virtual public CollisionManager{

    /**
     * Sweep And Prune engine, implemented using doubly linked lists
     * **Limitation:** if an object moves too fast, LSAP may miss
     * a collision.
     */
  public:
    typedef std::shared_ptr<LSAP> PTR;

  protected:
    /// objects added to the manager
    std::map< GameObject::PTR, AABB *> m_objects;

  private:

    /** First EndPoint on xAxis (not a real point, but a sentinel)*/
    EndPoint * xAxis;

    /** Second EndPoint on xAxis (not a real point, but a sentinel)*/
    EndPoint * yAxis;

    /** 
     * @brief Swap two EndPoints.
     * @details p2 has to be the direct follower of EndPoint after p1**
     * @param p1 first EndPoint
     * @param p2 second EndPoint
     */
    void swap(EndPoint * p1, EndPoint * p2);

    /**
     * @brief A collision between two AABB on one axis
     * no collision on equality (>/<)
     */
    bool partialCollisionCheck(const AABB & a, const AABB & b, int dim);

    /**
     * @brief Checks if two AABB collide using 2 axises
     * @see partialCollisionCheck
     */
    bool collisionCheck(const AABB & b1, const AABB & b2);

    /** @brief Update EndPoint place and call the appropriate function in case 
     * of collision/separation. 
     * @details Does not affect the EndPoint.value, which 
     * must be updated before calling updateEndPoint.
     * @param pt the EndPoint to update
     */
    void updateAxis(EndPoint * min, EndPoint * max);
    
    void sendCollision(AABB * a1, AABB * a2, Collision::Trigger) const;

  public:

    LSAP ();

    virtual ~LSAP ();

    /**
     * @brief Creates a bounding box attached to a Collider and insert its
     * points in xAxis and yAxis (keep it sorted)
     * @param c Object (Collider) attached to the new bounding box
     *          to insert in the list
     */
    void addObject(GameObject::PTR go);

    /**
     * @brief Updates Collider's EndPoints position in CollisionManger. 
     * @details Detects collisions and separation and acts according to 
     * actionManager. Should be called as soon as an object moves.
     * @param c Object to update
     */
    void updateObject(GameObject::PTR go);  
  
    virtual void update();

    /**
     * @brief Remove a bounding box attached to a Collider 
     * @param c Object attached to the bounding box to remove
     */
    void removeObject(GameObject::PTR go);

    static PTR create();

  };
}
#endif
