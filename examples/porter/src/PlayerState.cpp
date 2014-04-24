#include "PlayerState.hpp"

#include <iostream> // TODO remove

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{

}

bool PlayerState::onEnter()
{
  std::cout << "Player enters state "<< this << std::endl;
  return m_enter();
}

bool PlayerState::onExit()
{
  std::cout << "Player leaves state "<< this << std::endl;
  return m_exit();
}
