#ifndef PLAYER_STATE_FACTORY_HPP
#define PLAYER_STATE_FACTORY_HPP

#include "PlayerState.hpp"

class PlayerStateFactory
{

public:
  static PlayerState * create(const std::string& id,
                              std::function<bool()> enter,
                              std::function<bool()> exit);

};

#endif
