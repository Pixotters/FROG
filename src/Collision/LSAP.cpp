#include <map>
#include <climits>
#include <iostream>

#include "FROG/Collision/LSAP.hpp"

namespace frog {

  LSAP::LSAP (ActionManager * am) 
    : CollisionManager<Collider>() 
  {
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

  void LSAP::addObject(std::shared_ptr<GameObject> go) {
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

  void LSAP::updateObject(std::shared_ptr<GameObject> go) {
    auto f = m_objects.find(go);
    if (f != m_objects.end() )
      {
        f->second->updateEPValues();
        updateAxis(f->second->min[0], f->second->max[0]);
        updateAxis(f->second->min[1], f->second->max[1]);
      }
  }
  
  void LSAP::removeObject(std::shared_ptr<GameObject> go) {
    auto find = m_objects.find(go);
    if (find != m_objects.end() )
      {
        delete find->second;
        m_objects.erase(find);        
      }
  }

  void LSAP::swap(EndPoint * p1, EndPoint * p2) {
    if (p2->next != NULL) p2->next->prev = p1;
    if (p1->prev != NULL) p1->prev->next = p2;
    p1->next = p2->next;
    p2->next = p1;  
    p2->prev = p1->prev;
    p1->prev = p2;            
  }

  bool LSAP::partialCollisionCheck(const AABB & a, const AABB & b, int dim) {
    return !(a.min[dim]->value > b.max[dim]->value
             || a.max[dim]->value < b.min[dim]->value);
  }

  bool LSAP::collisionCheck(const AABB & b1, const AABB & b2) {
    return partialCollisionCheck (b1, b2, 0)
      && partialCollisionCheck (b1, b2, 1);
  }

  void LSAP::updateAxis(EndPoint * min, EndPoint * max) {
        
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
            std::cerr << "COLLISION OCCURED " << std::endl;
            //            this->actionManager->onCollision(pt->owner->owner,
            //                                             tmp->owner->owner);
          }
        } else if (doSeparate(pt, tmp)) {
                    std::cerr << "SEPARATION OCCURED " << std::endl;
                    //          this->actionManager->onSeparation(pt->owner->owner,
                    //     tmp->owner->owner);
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

  void LSAP::update()
  {
    for (auto& c : m_objects)
      {
        updateObject(c.first);
      }
  }


}
