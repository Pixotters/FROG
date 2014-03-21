#ifndef CONTROLMANAGER_HPP
#define CONTROLMANAGER_HPP

#include <map>

#include <iostream> //TODO remove

template <typename IN, typename OUT>
class ControlManager{

  //// attributes ////
protected:
  std::map< IN *, OUT * > m_binding;

  //// operations ////
public:
  ControlManager();
  virtual ~ControlManager();
  std::map< IN *, OUT * > getBinding() const;
  OUT * get(IN *) const;
  void suscribe(IN *, OUT *);
  OUT * set(IN *, OUT *);
  void unsuscribe(IN *);
  void clear();

};

#include "ControlManager.inl"

#endif
