#include "PlayerState.hpp"

using namespace frog;

PlayerState::PlayerState(const sf::Time& lt,
                         const Command::PTR& _onEnter, 
                         const Command::PTR& _onUpdate,
                         const Command::PTR& _onExit,
                         PlayerState * nextState)
  : State(),
    lifetime(lt), 
    onEnter(_onEnter),
    onUpdate(_onUpdate),
    onExit(_onExit),
    next(nextState)
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::addCommand(const sf::Time& time, 
                             const Command::PTR& command)
{
  auto insert = std::make_pair(time, command);
  commands.push_back( std::make_pair(insert, false) );
}

void PlayerState::resetCommands()
{
  for (auto& cmd : commands)
    {
      cmd.second = false;
    }
}

void PlayerState::enter()
{
  (*onEnter)();
}

void PlayerState::update()
{
  (*onUpdate)();
}

void PlayerState::exit()
{
  (*onExit)();
}

void PlayerState::changeNext(PlayerState * _next)
{
  next = _next;
}

sf::Time PlayerState::getLifetime() const
{
  return lifetime;
}

PlayerState * PlayerState::getNext() const
{
  return next;
}

std::vector< std::pair< std::pair<sf::Time, frog::Command::PTR>,
                          bool > > PlayerState::getCommands() const
{
  return commands;
}

PlayerState::PTR PlayerState::create(const sf::Time& lifetime,
                                     const Command::PTR& enter, 
                                     const Command::PTR& update,
                                     const Command::PTR& exit,
                                     PlayerState * next)
{
  return PTR( new PlayerState(lifetime, enter, update, exit, next) );
}
