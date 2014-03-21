#ifndef CTRL_ABSTRACTCONTROLLER_HPP
#define CTRL_ABSTRACTCONTROLLER_HPP

#include <list>
#include "Control/ControlManager.hpp"

#include <iostream>

namespace ctrl{

  template <typename IN>
  class AbstractController
  {
    //// attributes ////
  protected:
    std::list<IN *> m_check;
    std::list<IN *> m_output;

    //// operations ////
  public:
    AbstractController();
    virtual ~AbstractController();
    virtual void update() = 0;
    std::list<IN *> handle();
    std::list<IN *> getQueue() const;
    void suscribe(IN *);
    void unsuscribe(IN *);
    void cleanQueue();

  protected:
    void add(IN *);
    virtual bool check(IN *)= 0;
  
  };

#include "AbstractController.inl"

}
#endif
