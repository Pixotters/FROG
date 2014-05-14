#ifndef FROG_PAIRMANAGER_HPP
#define FROG_PAIRMANAGER_HPP

#include "FROG/Core/GameObject.hpp"
#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/Collision.hpp"
#include "FROG/Collision/CollisionManager.hpp"

#include <set>
#include <vector>

namespace frog{

  class PairManager : virtual public CollisionManager
  {

  private:
    std::vector<GameObject::PTR> m_objects;
    std::set< std::pair<GameObject *, GameObject *> > m_colliding;

  public:
  
    PairManager();
    virtual ~PairManager();
    virtual void addObject(const GameObject::PTR&);
    virtual void removeObject(const GameObject::PTR&);
    virtual void update();

  protected:
    virtual void updateObject(const GameObject::PTR&);
    bool isColliding(const GameObject::PTR&, const GameObject::PTR&) const;
    void addColliding(const GameObject::PTR&, const GameObject::PTR&);
    void removeColliding(const GameObject::PTR&, const GameObject::PTR&);
    void sendCollision(const GameObject::PTR&,
                       const GameObject::PTR&,
                       const Collider::PTR&,
                       const Collider::PTR&,
                       Collision::Trigger) const;
    bool collide(const Collider::PTR&, const Collider::PTR&) const;
  };

}

#endif
