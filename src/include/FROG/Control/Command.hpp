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

#ifndef FROG_COMMAND_HPP
#define FROG_COMMAND_HPP

#include <memory>

namespace frog{

  /*!
   * Command handles an action. This class is abstract and should be inherited 
   * while defining execute(). 
   */
  class Command
  {

  public:
    typedef std::shared_ptr<Command> PTR;

    //// operations ////
  public:

    Command();

    virtual ~Command();

    /*!
     * @brief Performs the command. 
     */
    virtual void execute() = 0;

    /*!
     * @brief Shortcut for execute()
     */
    void operator()();

    /*!
     * @brief Undoes the action trigger by execution
     * @detail If not overloaded, does nothing
     */
    void undo();

  };

}

#endif
