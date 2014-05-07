#include "FROG/Collision/EndPoint.hpp"

#include "FROG/Collision/AABB.hpp"

namespace frog{

  EndPoint::EndPoint (AABB* o,int v,bool m, EndPoint* p,EndPoint* n) :
    owner(o), value(v), isMin(m), prev(p), next(n) {}
    
  EndPoint::~EndPoint () {
    if (this->prev != nullptr) {
      this->prev->next = this->next;
    }
    if (this->next != nullptr) {
      this->next->prev = this->prev;
    }
  }

}
