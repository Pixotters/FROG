
template <class State>
FSM<State>::FSM()
{

}

template <class State>
FSM<State>::~FSM()
{

}

template <class State>
void FSM<State>::push(State * s)
{
  m_stack.push(s);
  s->onEnter();
}

template <class State>
State * FSM<State>::change(State * s)
{
  State * old;
  try
    {
      old = pop();
    }catch(Empty e)
    {
      old = nullptr;
    }
  push(s);
  return old;
}


template <class State>
State * FSM<State>::pop() throw (Empty)
{
  if( not m_stack.empty() )
    {
      State * s = m_stack.top();
      if  ( s->onExit() )
        {
          m_stack.pop();
          return s;
        }else
        {
          return nullptr;
        }
    }else
    {
      throw Empty();
    }

}

template <class State>
State * FSM<State>::top()
{
  return m_stack.top();
}

template <class State>
bool FSM<State>::isEmpty() const
{
  return m_stack.empty();
}

template <class State>
void FSM<State>::clear()
{
  while( not m_stack.empty() )
    {
      pop();
    }
}



