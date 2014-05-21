#include "PlayerStateFactory.hpp"

#include <FROG/Control/Function.hpp>

#include <iostream> // TODO remove

using namespace frog;

PlayerStateFactory::PlayerStateFactory(const frog::GameObject::PTR& p1, 
                                       const frog::GameObject::PTR& mirror1,
                                       const frog::GameObject::PTR& p2)
  : anim( p1->getComponent<Animator<std::string>>("RENDERING") ),
    anim_mirror( mirror1->getComponent<Animator<std::string>>("RENDERING") ),
    current( p1->getProperty<CharacterPlayed>("character") ),
    other( p2->getProperty<CharacterPlayed>("character") )
{

}

PlayerStateFactory::~PlayerStateFactory()
{
}

PlayerState::PTR PlayerStateFactory::get(PlayerState::ID id)
{
  auto find = states.find(id);
  if (find != states.end() )
    {
      return find->second;
    }else
    {
      return createState(id);
    }
}


PlayerStateFactory::PTR PlayerStateFactory::create(const GameObject::PTR& p1, 
                                                   const GameObject::PTR& m1, 
                                                   const GameObject::PTR& p2)
{
  return PTR( new PlayerStateFactory(p1, m1, p2) );
}

PlayerState::PTR PlayerStateFactory::createState(PlayerState::ID id)
{
  switch(id)
    {
    case PlayerState::STAND:
      return createStand();
      break;
    case PlayerState::PUNCH_L:
      return createPunchL();
      break;
    case PlayerState::PUNCH_M:
      return createPunchM();
      break;
    case PlayerState::PUNCH_R:
      return createPunchR();
      break;
    default:
      return createStand();
      break;
    }
}

PlayerState::PTR PlayerStateFactory::createStand()
{
  auto enter = Function::create([this](){
      std::cerr << "entering Stand" << std::endl;
      anim->playAnimation("stand");
      anim_mirror->playAnimation("stand");
    });
  auto none = Function::create([](){});
  auto standState = PlayerState::create(sf::seconds(0.6f), enter, none, none);
  standState->changeNext( standState.get() );
  states.emplace(PlayerState::STAND, standState);
  return standState;
}

PlayerState::PTR PlayerStateFactory::createPunchL()
{
  auto enter = Function::create([this](){
      std::cerr << "entering PunchL" << std::endl;
      anim->playAnimation("punchL");
      anim_mirror->playAnimation("punchL");
    });
  auto none = Function::create([](){});
  auto punchState = PlayerState::create(sf::seconds(1.0f), enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::PUNCH_L, punchState);
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchM");
      anim_mirror->playAnimation("punchM");
    });
  auto none = Function::create([](){});
  auto punchState = PlayerState::create(sf::seconds(1.4f), enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::PUNCH_M, punchState);
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchR");
      anim_mirror->playAnimation("punchR");
    });
  auto none = Function::create([](){});
  auto punchState = PlayerState::create(sf::seconds(1.0f), enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::PUNCH_R, punchState);
  return punchState;
}


