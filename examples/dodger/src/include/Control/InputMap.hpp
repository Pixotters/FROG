#ifndef CTRL_INPUTMAP_HPP
#define CTRL_INPUTMAP_HPP

#include "Main/Translator.hpp"

namespace frog{

  namespace ctrl {
 
    typedef Translator<Input *, Command *> InputMap;

  }

}

#endif
