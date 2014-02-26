#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Component
{
  //// attributes ////
protected:

  //// operations ////
public:
  Component(){ }
  virtual ~Component(){ }

  virtual void update() = 0;
  

};

#endif
