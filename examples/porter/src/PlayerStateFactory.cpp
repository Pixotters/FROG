#include "PlayerStateFactory.hpp"

PlayerState * PlayerStateFactory::create(const std::string& id,
                                         std::function<bool()> enter,
                                         std::function<bool()> exit)
{
  PlayerState * ps = new PlayerState(id);
  ps->m_enter = enter;
  ps->m_exit = exit;
  return ps;
}
