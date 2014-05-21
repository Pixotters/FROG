#include "PlayerStateFactory.hpp"

#include <FROG/Control/Function.hpp>

#include <iostream> // TODO remove

using namespace frog;


static auto none = Function::create([](){});

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
    case PlayerState::DODGE_L:
      return createDodgeL();
      break;
    case PlayerState::DODGE_M:
      return createDodgeM();
      break;
    case PlayerState::DODGE_R:
      return createDodgeR();
      break;
    default:
      return createStand();
      break;
    }
}

PlayerState::PTR PlayerStateFactory::createStand()
{
  auto enter = Function::create([this](){
      anim->playAnimation("stand");
      anim_mirror->playAnimation("stand");
    });
  auto standState = PlayerState::create(PlayerState::STAND,
                                        sf::seconds(0.6f), 
                                        enter, none, none);
  standState->changeNext( standState.get() );
  states.emplace(PlayerState::STAND, standState);
  return standState;
}

PlayerState::PTR PlayerStateFactory::createPunchL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchL");
      anim_mirror->playAnimation("punchL");
      current.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_L, sf::seconds(1.0f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  auto strike = Function::create([this](){
      if (other.vulnerable)
        {
          other.vulnerable = false;
          other.receivedHits++;
          other.loseHealth(40);
        }
    });
  punchState->addCommand(sf::seconds(0.4f), strike);
  states.emplace(PlayerState::PUNCH_L, punchState);
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchM");
      anim_mirror->playAnimation("punchM");
      current.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_M,
                                        sf::seconds(1.4f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::PUNCH_M, punchState);
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchR");
      anim_mirror->playAnimation("punchR");
      current.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_R,
                                        sf::seconds(1.0f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::PUNCH_R, punchState);
  return punchState;
}


PlayerState::PTR PlayerStateFactory::createDodgeL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeL");
      anim_mirror->playAnimation("dodgeL");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_L,
                                        sf::seconds(0.3f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::DODGE_L, dodgeState);
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeM");
      anim_mirror->playAnimation("dodgeM");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_M,
                                        sf::seconds(0.3f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::DODGE_M, dodgeState);
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeR");
      anim_mirror->playAnimation("dodgeR");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_R, 
                                        sf::seconds(0.3f), 
                                        enter, none, none, 
                                        get(PlayerState::STAND).get() );
  states.emplace(PlayerState::DODGE_R, dodgeState);
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createStroke()
{
  auto enter = Function::create([this](){
      anim->playAnimation("stroke");
      anim_mirror->playAnimation("stroke");
    });
  auto state = PlayerState::create(PlayerState::STROKE,
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::STAND).get() );
  states.emplace(PlayerState::STROKE, state);
  return state;
}

PlayerState::PTR PlayerStateFactory::createKO()
{
 auto enter = Function::create([this](){
      anim->playAnimation("KO");
      anim_mirror->playAnimation("KO");
    });
 auto state = PlayerState::create(PlayerState::KO,
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::RAISING).get() );
  states.emplace(PlayerState::KO, state);
  return state;
}

PlayerState::PTR PlayerStateFactory::createRaising()
{
 auto enter = Function::create([this](){
      anim->playAnimation("raising");
      anim_mirror->playAnimation("raising");
    });
 auto state = PlayerState::create(PlayerState::RAISING, 
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::STAND).get() );
  states.emplace(PlayerState::RAISING, state);
  return state;
}

PlayerState::PTR PlayerStateFactory::createHappy()
{
 auto enter = Function::create([this](){
     anim->playAnimation("happy", true);
     anim_mirror->playAnimation("happy", true);
    });
 auto state = PlayerState::create(PlayerState::HAPPY,
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::STAND).get() );
  states.emplace(PlayerState::HAPPY, state);
  return state;
}

PlayerState::PTR PlayerStateFactory::createStun()
{
 auto enter = Function::create([this](){
     anim->playAnimation("stun", true);
     anim_mirror->playAnimation("stun", true);
    });
 auto state = PlayerState::create(PlayerState::STUN,
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::STAND).get() );
  states.emplace(PlayerState::STUN, state);
  return state;
}

PlayerState::PTR PlayerStateFactory::createBreathing()
{
 auto enter = Function::create([this](){
     anim->playAnimation("breathing", true);
     anim_mirror->playAnimation("breathing", true);
    });
 auto state = PlayerState::create(PlayerState::BREATHING,
                                   sf::seconds(0.3f), 
                                   enter, none, none, 
                                   get(PlayerState::STAND).get() );
  states.emplace(PlayerState::BREATHING, state);
  return state;
}

