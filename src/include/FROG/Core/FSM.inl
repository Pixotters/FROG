/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

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

