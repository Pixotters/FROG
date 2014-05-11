#ifndef FROG_COMMAND_HPP
#define FROG_COMMAND_HPP

#include <memory>
#include <string>

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
