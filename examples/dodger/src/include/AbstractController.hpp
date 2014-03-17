#ifndef ABSTRACTCONTROLLER_HPP
#define ABSTRACTCONTROLLER_HPP

#include <map>
#include <queue>
#include <list>

template <typename IN, typename OUT>
class AbstractController
{
  //// attributes ////
protected:
  std::map< IN *, OUT * > m_binding;
  std::queue<OUT * > m_output;

  //// operations ////
public:
  AbstractController();
  virtual ~AbstractController();
  virtual void handle();
  void suscribe(IN *, OUT *);
  void unsuscribe(IN *);
  void clear();
  std::queue<OUT *> getQueue() const;

protected:
  void add(OUT *);
  virtual bool handle(IN *);
  void cleanQueue();
  
};

#include "AbstractController.inl"

#endif
