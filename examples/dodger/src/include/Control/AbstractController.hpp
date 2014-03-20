#ifndef CTRL_ABSTRACTCONTROLLER_HPP
#define CTRL_ABSTRACTCONTROLLER_HPP

#include <queue>
#include "Control/ControlManager.hpp"

#include <iostream>

namespace ctrl{

  template <typename IN, typename OUT>
  class AbstractController
  {
    //// attributes ////
  protected:
    std::queue<OUT * > m_output;
    ControlManager<IN, OUT> * m_controlManager;

    //// operations ////
  public:
    AbstractController();
    virtual ~AbstractController();
    virtual void update() = 0;
    std::queue<OUT *> handle();
    std::queue<OUT *> getQueue() const;
    ControlManager<IN, OUT> * setManager(ControlManager<IN, OUT> *);
    ControlManager<IN, OUT> * getManager() const;

  protected:
    void add(OUT *);
    virtual bool occurred(IN *)= 0;
    void cleanQueue();
  
  };

#include "AbstractController.inl"

}
#endif
