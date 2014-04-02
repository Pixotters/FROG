#ifndef FROG_CTRL_INPUTMAP_HPP
#define FROG_CTRL_INPUTMAP_HPP

#include "FROG/Translator.hpp"

namespace frog{

  namespace ctrl {
 
    typedef Translator<Input *, Command *> InputMap;

  }

}

#endif
