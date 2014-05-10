#include "PlayerState.hpp"

PlayerState::PlayerState(ID id)
  : m_id(id)
{

}

PlayerState::~PlayerState()
{

}

bool PlayerState::onEnter()
{
  return m_enter();
}

bool PlayerState::onExit()
{
  return m_exit();
}

std::string PlayerState::getId() const
{
  return m_id;
}
