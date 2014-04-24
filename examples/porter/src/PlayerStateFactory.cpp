#include "PlayerStateFactory.hpp"

PlayerState * PlayerStateFactory::create(std::function<bool()> enter,
                                         std::function<bool()> exit)
{
  PlayerState * ps = new PlayerState;
  ps->m_enter = enter;
  ps->m_exit = exit;
  return ps;
}
