#ifndef FROG_COLLISION_MANAGER_HPP
#define FROG_COLLISION_MANAGER_HPP 1

/** Interface for collision managers */

template <typename Obj> class CollisionManager  {

public:

  CollisionManager(){};
  
  virtual ~CollisionManager() {}
  
  virtual void addObject(Obj *) = 0;
  
  virtual void updateObject(Obj *) = 0;
  
  virtual void removeObject(Obj *) = 0;

  virtual void update() = 0;
  
};

#endif
