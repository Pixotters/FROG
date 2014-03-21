#ifndef FILTER_HPP
#define FILTER_HPP

#include <list>

#include <iostream>

namespace ctrl{

  template <typename IN>
  class Filter
  {
    //// attributes ////
  protected:
    std::list<IN *> m_check;
    std::list<IN *> m_output;

    //// operations ////
  public:
    Filter();
    virtual ~Filter();
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

#include "Filter.inl"

}
#endif
