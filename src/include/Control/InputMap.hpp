#ifndef CTRL_INPUTMAP_HPP
#define CTRL_INPUTMAP_HPP

#include "Translator.hpp"

namespace frog{

  namespace ctrl {
 
    typedef Translator<Input *, Command *> InputMap;

  }

}

#endif
