#ifndef PLAYERSTATEFACTORY_HPP
#define PLAYERSTATEFACTORY_HPP

#include "CharacterPlayed.hpp"
//#include "Match.hpp"
#include "PlayerState.hpp"

#include <FROG/Core/GameObject.hpp>
#include <FROG/Rendering/Animator.hpp>

#include <map>
#include <memory>

class Match;

class PlayerStateFactory
{

public:
  typedef std::shared_ptr<PlayerStateFactory> PTR;

private:
  Match * match;
  frog::Animator<std::string>::PTR anim;
  frog::GameObject::PTR& current;
  frog::GameObject::PTR& other;
  CharacterPlayed& currentCharacter;

public:
  PlayerStateFactory(Match * match,
                     frog::GameObject::PTR& p1, 
                     frog::GameObject::PTR& p2);
  virtual ~PlayerStateFactory();
  static PTR create(Match * match,
                    frog::GameObject::PTR& p1, 
                    frog::GameObject::PTR& p2);
  PlayerState::PTR createState(PlayerState::ID);
  PlayerState::PTR createStand();
  PlayerState::PTR createPunchL();
  PlayerState::PTR createPunchM();
  PlayerState::PTR createPunchR();
  PlayerState::PTR createDodgeL();
  PlayerState::PTR createDodgeM();
  PlayerState::PTR createDodgeR();
  PlayerState::PTR createStroke();
  PlayerState::PTR createKO();
  PlayerState::PTR createRaising();
  PlayerState::PTR createHappy();
  PlayerState::PTR createStun();
  PlayerState::PTR createBreathing();
};

#endif
