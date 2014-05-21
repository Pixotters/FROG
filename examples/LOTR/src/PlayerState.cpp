#include "PlayerState.hpp"

using namespace frog;

PlayerState::PlayerState(ID _id,
                         const sf::Time& lt,
                         Command::PTR _onEnter, 
                         Command::PTR _onUpdate,
                         Command::PTR _onExit,
                         PlayerState * nextState)
  : State(),
    id(_id),
    lifetime(lt), 
    onEnter(_onEnter),
    onUpdate(_onUpdate),
    onExit(_onExit),
    next(nextState)
{

}

PlayerState::PlayerState(const PlayerState& other)
  : State(), 
    id(other.id),
    lifetime(other.lifetime),
    onEnter(other.onEnter),
    onUpdate(other.onUpdate),
    onExit(other.onExit),
    next(other.next),
    commands(other.commands)
{

}


PlayerState::~PlayerState()
{
}

void PlayerState::addCommand(const sf::Time& time, 
                             Command::PTR command)
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

PlayerState::ID PlayerState::getID() const
{
  return id;
}

std::vector< std::pair< std::pair<sf::Time, frog::Command::PTR>,
                          bool > > PlayerState::getCommands() const
{
  return commands;
}

PlayerState::PTR PlayerState::create(ID id,
                                     const sf::Time& lifetime,
                                     Command::PTR enter, 
                                     Command::PTR update,
                                     Command::PTR exit,
                                     PlayerState * next)
{
  return PTR( new PlayerState(id, lifetime, enter, update, exit, next) );
}

PlayerState::PTR PlayerState::create(const PlayerState& other)
{
  return PTR(new PlayerState(other) );
}
