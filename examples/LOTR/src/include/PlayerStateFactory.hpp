#ifndef PLAYERSTATEFACTORY_HPP
#define PLAYERSTATEFACTORY_HPP

#include "CharacterPlayed.hpp"
#include "PlayerState.hpp"

#include <FROG/Core/GameObject.hpp>
#include <FROG/Rendering/Animator.hpp>

#include <map>
#include <memory>

class PlayerStateFactory
{

public:
  typedef std::shared_ptr<PlayerStateFactory> PTR;

private:
  frog::Animator<std::string>::PTR anim;
  frog::Animator<std::string>::PTR anim_mirror;
  CharacterPlayed& current;
  CharacterPlayed& other;
  std::map< PlayerState::ID, PlayerState::PTR > states;

public:
  PlayerStateFactory(const frog::GameObject::PTR& p1, 
                     const frog::GameObject::PTR& mirror1, 
                     const frog::GameObject::PTR& p2);
  virtual ~PlayerStateFactory();
  PlayerState::PTR get(PlayerState::ID);
  static PTR create(const frog::GameObject::PTR& p1, 
                    const frog::GameObject::PTR& mirror1, 
                    const frog::GameObject::PTR& p2);
  PlayerState::PTR createState(PlayerState::ID);
  PlayerState::PTR createStand();
  PlayerState::PTR createPunchL();
  PlayerState::PTR createPunchM();
  PlayerState::PTR createPunchR();
  PlayerState::PTR createDodgeL();
  PlayerState::PTR createDodgeM();
  PlayerState::PTR createDodgeR();
};

#endif
