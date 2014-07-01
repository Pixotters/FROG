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

    void push(PTR_S s);
    void push(S * s); // avoid this one if not dynamically allocated

    void pop() throw(std::logic_error);

    S& top();

    void change(PTR_S s);
    void change(S * s); // avoid this one if not dynamically allocated
  
    bool isEmpty() const;

    void clear();

  };

}

#include "FROG/Core/FSM.inl"

#endif
