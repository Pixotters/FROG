#ifndef PLAYERSTATEFACTORY_HPP
#define PLAYERSTATEFACTORY_HPP

#include "PlayerState.hpp"

class PlayerStateFactory
{

public:
  typedef std::shared_ptr<PlayerStateFactory> PTR;

public:
  frog::GameObject::PTR object1;
  frog::GameObject::PTR object2;
  PlayerMachine::PTR machine;
  std::map< std::string, PlayerState> map;

public:
  PlayerStateFactory(const frog::GameObject::PTR&,
                     const frog::GameObject::PTR&,
                     const PlayerMachine::PTR&);
  virtual ~PlayerStateFactory();
  PlayerState get(const std::string&) const;

private:
  void createStates();

};

#endif

