#include "FROG/Collision/PairManager.hpp"

#include "FROG/Collision/Collision.hpp"

namespace frog{

  PairManager::PairManager()
    : CollisionManager()
  {

  }

  PairManager::~PairManager()
  {
    m_objects.clear();
    m_colliding.clear();
  }

  void PairManager::addObject(const GameObject::PTR& go)
  {
    auto end = m_objects.end();
    for (auto it = m_objects.begin(); it != end; it++) 
      {
        if (*it == go)
          return;
      }
    m_objects.push_back(go);
  }

  void PairManager::removeObject(const GameObject::PTR& go)
  {
    auto end = m_objects.end();
    for (auto it = m_objects.begin(); it != end; it++) 
      {
        if (*it == go)
          {
            m_objects.erase(it);
            break;
          }
      }
    for (auto pair: m_colliding)
      {
        if (pair.first == go.get() or pair.second == go.get() )
          {
            pair.first = nullptr;
            pair.second = nullptr;
          }
      }
    auto nullpair = std::make_pair(nullptr, nullptr);
    m_colliding.erase(nullpair);
  }

  void PairManager::updateObject(const GameObject::PTR& go)
  {
  
  }



  void PairManager::update()
  {
    auto t = m_objects.size();
    for (unsigned int i = 0; i < t; i++)
      {
        auto& o1 = m_objects.at(i);
        for (unsigned int j = i+1; j < t; j++)
          {
            auto& o2 = m_objects.at(j);
          
            auto r1 = o1->getComponent<Collider>("COLLIDER");
            auto r2 = o2->getComponent<Collider>("COLLIDER");
            // TODO remove
            auto bb1 = r1->getBoundingBox();
            auto bb2 = r2->getBoundingBox();
            if ( collide(r1, r2) or collide(r2, r1) )
              {
                addColliding(o1, o2);
                sendCollision(o1, o2, r1, r2, Collision::Trigger::COLLISION);
              }else
              {
                if ( isColliding(o1, o2) )
                  {
                    removeColliding(o1, o2);
                    sendCollision(o1, o2, r1, r2,Collision::Trigger::SEPARATION);
                  }
              }
          }
      }
  }


  bool PairManager::isColliding(const GameObject::PTR& o1, 
                                const GameObject::PTR& o2) const
  {
    auto end = m_colliding.end();
    return ( (m_colliding.find(std::make_pair(o1.get(), o2.get() ) ) != end)
             or (m_colliding.find(std::make_pair(o2.get(), o1.get()) ) != end) );
  }

  void PairManager::addColliding(const GameObject::PTR& o1, 
                                 const GameObject::PTR& o2)
  {
    m_colliding.insert( std::make_pair(o1.get(), o2.get() ) );
  }

  void PairManager::removeColliding(const GameObject::PTR& o1, 
                                    const GameObject::PTR& o2)
  {
    m_colliding.erase( std::make_pair(o1.get(), o2.get() ) );
    m_colliding.erase( std::make_pair(o2.get(), o1.get() ) );
  }

  void PairManager::sendCollision(const GameObject::PTR& o1,
                                  const GameObject::PTR& o2,
                                  const Collider::PTR& r1,
                                  const Collider::PTR& r2,
                                  Collision::Trigger tr) const
  {
    if (r1.get() != nullptr and r2.get() != nullptr)
      {
        Collision c(o1, o2, tr);
        r1->onCollision(c);
        if (r1.get() != nullptr and r2.get() != nullptr)
          {
            Collision c(o2, o1, tr);
            r2->onCollision(c);
          }
      }

  }


  bool PairManager::collide(const Collider::PTR& c1, 
                            const Collider::PTR& c2) const
  {
    BoxCollider::PTR b1, b2;
    RoundCollider::PTR r1, r2;
    b1 = std::dynamic_pointer_cast<BoxCollider>(c1);
    b2 = std::dynamic_pointer_cast<BoxCollider>(c2);
    r1 = std::dynamic_pointer_cast<RoundCollider>(c1);
    r2 = std::dynamic_pointer_cast<RoundCollider>(c2);
    if (b1 != nullptr and b2 != nullptr)
      {
        return collide(b1, b2);
      }else if (r1 != nullptr and r2 != nullptr)
      {
        return collide(r1, r2);
      }else if (b1 != nullptr and r2 != nullptr)
      {
        return collide(b1, r2);
      }else if (r1 != nullptr and b2 != nullptr)
      {
        return collide(r1, b2);
      }else
      {
        return false;
      }
  }

  bool PairManager::collide(const BoxCollider::PTR& b1, const BoxCollider::PTR& b2) const
  {
    return b1->getBoundingBox().intersects( b2->getBoundingBox() );
  }

  bool PairManager::collide(const RoundCollider::PTR& r1, const RoundCollider::PTR& r2) const
  {
    // TODO : real collision circle-circle
    return r1->getBoundingBox().intersects( r2->getBoundingBox() );
  }

  bool PairManager::collide(const BoxCollider::PTR& b1, const RoundCollider::PTR& r2) const
  {
    return b1->getBoundingBox().intersects( r2->getBoundingBox() );
  }

  bool PairManager::collide(const RoundCollider::PTR& r1, const BoxCollider::PTR& b2) const
  {
    return r1->getBoundingBox().intersects( b2->getBoundingBox() );
  }



}
