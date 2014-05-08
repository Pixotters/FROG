#ifndef FROG_COMMAND_HPP
#define FROG_COMMAND_HPP

#include <string>

namespace frog{

  /*!
   * Command handles an action. This class is abstract and should be inherited 
   * while defining execute(). 
   */
  class Command
  {
    //// attributes ////
  protected:

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
  };

}

#endif
