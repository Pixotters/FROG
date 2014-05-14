#ifndef FROG_FSM_HPP
#define FROG_FSM_HPP

#include <exception>
#include <memory>
#include <stack>

namespace frog{

  template <class S>
  class FSM
  {

  public:
    typedef std::shared_ptr<S> PTR_S;

  protected:
    std::stack< PTR_S > m_stack;

  public:

    FSM();

    virtual ~FSM();

    void push(PTR_S& s);
    void push(S * s); // avoid this one if not dynamically allocated

    void pop() throw(std::logic_error);

    S& top();

    void change(PTR_S& s);
    void change(S * s); // avoid this one if not dynamically allocated
  
    bool isEmpty() const;

    void clear();

  };

}

#include "FROG/Core/FSM.inl"

#endif
