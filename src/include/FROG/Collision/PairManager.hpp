/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_PAIRMANAGER_HPP
#define FROG_PAIRMANAGER_HPP

#include "FROG/Core/GameObject.hpp"
#include "FROG/Collision/Collider.hpp"
#include "FROG/Collision/BoxCollider.hpp"
#include "FROG/Collision/RoundCollider.hpp"
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
    bool collide(const BoxCollider::PTR&, const BoxCollider::PTR&) const;
    bool collide(const RoundCollider::PTR&, const RoundCollider::PTR&) const;
    bool collide(const BoxCollider::PTR&, const RoundCollider::PTR&) const;
    bool collide(const RoundCollider::PTR&, const BoxCollider::PTR&) const;
  };

}

#endif
