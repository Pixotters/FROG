#ifndef FROG_DEBUG_HPP
#define FROG_DEBUG_HPP

#include <iostream>
#include <sstream>
#include <string>

/*
 * @brief Prints a message on STDERR only if FROG_DEBUG has been defined
 * @param msg Message to print
 */
inline void print_debug(const std::string& msg)
{
#ifdef FROG_DEBUG
  std::cerr << msg << std::endl;
#endif
}

/*
 * @brief Prints a message on STDERR only if FROG_DEBUG has been defined
 * @param msg Message to print
 */
inline void print_debug(const std::ostringstream& msg)
{
#ifdef FROG_DEBUG
  std::cerr << msg.str() << std::endl;
#endif
}


#endif
