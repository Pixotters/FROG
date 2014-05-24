namespace frog{

  template <class S>
  FSM<S>::FSM()
  {

  }

  template <class S>
  FSM<S>::~FSM()
  {
    clear();
  }

  template <class S>
  void FSM<S>::push(S * s)
  {
    m_stack.push( PTR_S(s) );
    s->enter();
  }

  template <class S>
  void FSM<S>::push(PTR_S s)
  {
    m_stack.push( PTR_S(s) );
    s->enter();
  }

  template <class S>
  void FSM<S>::change(S * s)
  {
    if (not isEmpty() )
      pop();
    push(s);
  }

  template <class S>
  void FSM<S>::change(PTR_S s)
  {
    if (not isEmpty() )
      pop();
    push(s);
  }

  template <class S>
  void FSM<S>::pop() throw (std::logic_error)
  {
    if( not m_stack.empty() )
      {
        std::shared_ptr<S> s( m_stack.top() );
        m_stack.pop();
        s->exit();
        s.reset();
      }else
      {
        throw std::logic_error("FSM is empty");
      }

  }

  template <class S>
  S& FSM<S>::top()
  {
    return *(m_stack.top().get() );
  }

  template <class S>
  bool FSM<S>::isEmpty() const
  {
    return m_stack.empty();
  }

  template <class S>
  void FSM<S>::clear()
  {
    while( not m_stack.empty() )
      {
        pop();
      }
  }

}

