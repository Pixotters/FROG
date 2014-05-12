#include <map>
#include <climits>
#include <iostream> // TODO remove
#include <memory>

#include "FROG/Collision/LSAP.hpp"

namespace frog
{

  LSAP::LSAP () 
  : CollisionManager() 
  {
    /* not sure about the true/false values */
    xAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
    xAxis->next = new EndPoint(NULL, INT_MAX, false, xAxis, NULL);
    yAxis = new EndPoint(NULL, INT_MIN, true, NULL, NULL);
    yAxis->next = new EndPoint(NULL, INT_MAX, false, yAxis, NULL);
  }

  LSAP::~LSAP ()
  {
    
    /* delete all AABB will delete EndPoints */
    for (auto& couple : m_objects)
      {
        if (couple.second != nullptr)
        {
          delete couple.second;
        }
      }

    m_objects.clear();

    /* delete all sentinels */
    if (xAxis->next != nullptr)
      delete xAxis->next;
    if (xAxis != nullptr)
      delete xAxis;
    if (yAxis->next != nullptr)
      delete yAxis->next;
    if (yAxis != nullptr)
      delete yAxis;
  }

  void LSAP::addObject(std::shared_ptr<GameObject> go)
  {
    auto collider = go->getComponent<Collider>("COLLIDER");
    AABB * aabb = new AABB(collider);

    m_objects.emplace(go, aabb);
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

    updateObject(go);
  }

  void LSAP::updateObject(std::shared_ptr<GameObject> go)
  {
    auto f = m_objects.find(go);
    if (f != m_objects.end() )
      {
        f->second->updateEPValues();
        updateAxis(f->second->min[0], f->second->max[0]);
        updateAxis(f->second->min[1], f->second->max[1]);
      }
  }
  
  void LSAP::removeObject(std::shared_ptr<GameObject> go)
  {
    auto find = m_objects.find(go);
    if (find != m_objects.end() )
      {
        delete find->second;
        m_objects.erase(find);        
      }
    
  }

  void LSAP::swap(EndPoint * p1, EndPoint * p2)
  {
    if (p2->next != nullptr) p2->next->prev = p1;
    if (p1->prev != nullptr) p1->prev->next = p2;
    p1->next = p2->next;
    p2->next = p1;  
    p2->prev = p1->prev;
    p1->prev = p2;            
  }

  bool LSAP::partialCollisionCheck(const AABB & a, const AABB & b, int dim)
  {
    return not(a.min[dim]->value > b.max[dim]->value
               or a.max[dim]->value < b.min[dim]->value);
  }

  bool LSAP::collisionCheck(const AABB & b1, const AABB & b2)
  {
    return partialCollisionCheck (b1, b2, 0)
            and partialCollisionCheck (b1, b2, 1);
  }

  void LSAP::updateAxis(EndPoint * min, EndPoint * max)
  {

  /*
   * succ: function for getting the next EndPoint form another one
   * loop_cond: condition for loop break testing
   * swap_fun: function to swap two EndPoints with necessary operations
   * doCollide: function to tell if two objects which were not colliding
   *            are colliding now.
   * doSeparate: function to tell if two objects which were colliding
   *             are not colliding anymore.
   */

    auto update =
      [this]
      (EndPoint * pt,
       std::function<EndPoint*(EndPoint*)> succ,
       std::function<bool(EndPoint*pt,EndPoint*succ)> loop_cond,
       std::function<void(EndPoint*pt,EndPoint*succ)> swap_fun,
       std::function<bool(EndPoint*pt,EndPoint*succ)> doCollide,
       std::function<bool(EndPoint*pt,EndPoint*succ)> doSeparate)
      {
          
        EndPoint * tmp = succ(pt);

        if (!loop_cond(pt, tmp))
        {
          return false;
        }

        do
        {
          swap_fun(pt, tmp);
          if (doCollide(pt, tmp))
          {
            if (this->collisionCheck(*(pt->owner), *(tmp->owner)))
            {
              sendCollision(pt->owner, tmp->owner, Collision::COLLISION);
            }
          }
          else if (doSeparate(pt, tmp))
          {
            sendCollision(pt->owner, tmp->owner, Collision::SEPARATION);
          }
          tmp = succ(pt);
        }
        while (loop_cond(pt, tmp));

      return true;
    };

    /* No collision detected on equality (<=/>=). */

    /* BEGIN: "from left to right"  */

    auto prev = [](EndPoint *p)
      {
        return p->prev;
      };

    auto prev_cond = [](EndPoint * pt, EndPoint * succ)
      { 
        if (pt != nullptr and succ != nullptr)
        {
          return pt->value < succ->value;
        }
        else
        {
          return false;
        } 
      };

    auto prev_swap = [this](EndPoint * pt, EndPoint * succ)
      {
        swap(succ, pt);
      };

    auto prev_col = [](EndPoint *pt, EndPoint *succ)
      { 
        return pt->isMin && !succ->isMin;
      };

    auto prev_sep = [](EndPoint *pt, EndPoint *succ)
      { 
        return !pt->isMin and succ->isMin;
      };
    /* END: "from left to right"  */

    /* BEGIN: "from right to left"  */
    auto next = [](EndPoint *p)
      {
        return p->next;
      };

    auto next_cond = [](EndPoint * pt, EndPoint * succ)
      {
        if (pt != nullptr and succ != nullptr)
        {
          return pt->value > succ->value;
        }
        else
        {
          return false;
        }
      };

    auto next_swap = [this](EndPoint * pt, EndPoint * succ)
      {
        swap(pt, succ);
      };

    auto next_col = [](EndPoint *pt, EndPoint *succ)
      { 
        return !pt->isMin && succ->isMin;
      };

    auto next_sep = [](EndPoint *pt, EndPoint *succ)
      { 
        return pt->isMin && !succ->isMin;
      };
    /* END: "from right to left" */

    /* Test if when need to update the position of the points in the list.
     * First look at order regarding to successors. If the place still the
     * same, look for an update according to predecessors
     * BINOR force update and allow to use a boolean test */
    if(not(update(max, next, next_cond, next_swap, next_col, next_sep) |
           update(min, next, next_cond, next_swap, next_col, next_sep))) {
      update(min, prev, prev_cond, prev_swap, prev_col, prev_sep);
      update(max, prev, prev_cond, prev_swap, prev_col, prev_sep);
    }

  }

  void LSAP::update()
  {
    for (auto & c : m_objects)
      {
        updateObject(c.first);
      }
  }

  void LSAP::sendCollision(AABB * a1, AABB * a2, Collision::Trigger tr) const
  {
    std::shared_ptr<GameObject> g1, g2;
    for (auto it: m_objects)
    {
      if (it.second == a1)
      {
        g1 = it.first;
      }        
      if (it.second == a2)
      {
        g2 = it.first;
      }
    }
    if (g1.get() != nullptr and g2.get() != nullptr
        and a1 != nullptr)
      {
        Collision c(g1, g2, tr);
        a1->owner->onCollision(c);
      }
    // re-testing in case first collision destroy one of the two elements
    if (g1 != nullptr and g2 != nullptr
        and a2 != nullptr)
      {
        Collision c(g2, g1, tr);
        a2->owner->onCollision(c);
      }    
  }

}
