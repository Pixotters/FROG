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
    for (unsigned int i = 0; i < t/2; i++)
      {
        auto& o1 = m_objects.at(i);
        for (unsigned int j = 0; j <= t/2; j++)
          {
            auto& o2 = m_objects.at(j);
          
            auto c1 = o1->getComponent<Collider>("COLLIDER");
            auto c2 = o2->getComponent<Collider>("COLLIDER");
            if ( collide(c1, c2) or collide(c2, c1) )
              {
                addColliding(o1, o2);
                sendCollision(o1, o2, c1, c2, Collision::Trigger::COLLISION);
              }else
              {
                if ( isColliding(o1, o2) )
                  {
                    removeColliding(o1, o2);
                    sendCollision(o1, o2, c1, c2,Collision::Trigger::SEPARATION);
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
                                  const Collider::PTR& c1,
                                  const Collider::PTR& c2,
                                  Collision::Trigger tr) const
  {
    if (c1.get() != nullptr and c2.get() != nullptr)
      {
        Collision c(o1, o2, tr);
        c1->onCollision(c);
        
        if (c1.get() != nullptr and c2.get() != nullptr)
          {
            Collision c(o2, o1, tr);
            c2->onCollision(c);
          }
      }

  }


  bool PairManager::collide(const Collider::PTR& c1, 
                            const Collider::PTR& c2) const
  {
    
  }

}
