#include "PlayerMachine.hpp"
#include "PlayerState.hpp"
#include <FROG/Core/ComponentHolder.hpp>
#include <FROG/Core/GameObject.hpp>
#include <FROG/Rendering/Animator.hpp>

#include <iostream> // TODO remove

using namespace frog;

PlayerMachine::PlayerMachine()
{
}

PlayerMachine::~PlayerMachine()
{
}

void PlayerMachine::resetCount()
{
  frame = 0;
}

void PlayerMachine::update(const ComponentHolder&)
{
  frame++;
  if (not isEmpty() )
    top().update();
}
