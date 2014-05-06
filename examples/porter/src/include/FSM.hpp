#ifndef FSM_HPP
#define FSM_HPP

#include <exception>

#include <stack>

template <class State>
class FSM
{

public:
  class Empty : virtual public std::exception
  {

    virtual const char* what() const throw()
    {
      return "FSM is empty";
    }
    
  } ;

protected:
  std::stack<State *> m_stack;

public:

  FSM();

  virtual ~FSM();

  void push(State * s);

  State * pop() throw (Empty);

  State * top();

  State * change(State * s);
  
  bool isEmpty() const;

  void clear();

};

#include "FSM.inl"

#endif
