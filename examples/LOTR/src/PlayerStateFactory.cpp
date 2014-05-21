#include "PlayerStateFactory.hpp"
#include "PlayerMachine.hpp"

#include <FROG/Control/Function.hpp>

#include <iostream> // TODO remove

using namespace frog;


static auto none = Function::create([](){});

PlayerStateFactory::PlayerStateFactory(Match * _match,
                                       frog::GameObject::PTR& p1, 
                                       frog::GameObject::PTR& p2)
  : match(_match),
    current(p1),
    other(p2),
    anim(p1->getComponent<Animator<std::string>>("RENDERING") ),
    currentCharacter( p1->getProperty<CharacterPlayed>("character") )
{
  std::cout << "factory" << std::endl;
}

PlayerStateFactory::~PlayerStateFactory()
{
}

PlayerStateFactory::PTR PlayerStateFactory::create(Match * _match, 
                                                   GameObject::PTR& p1, 
                                                   GameObject::PTR& p2)
{
  return PTR( new PlayerStateFactory(_match, p1, p2) );
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
    case PlayerState::STROKE:
      return createStroke();
      break;
    case PlayerState::KO:
      return createKO();
      break;
    case PlayerState::RAISING:
      return createRaising();
      break;
    case PlayerState::HAPPY:
      return createHappy();
      break;
    case PlayerState::STUN:
      return createStun();
      break;
    case PlayerState::BREATHING:
      return createBreathing();
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
    });
  auto standState = PlayerState::create(PlayerState::STAND,
                                        sf::seconds(0.6f), 
                                        enter, none, none);
  standState->changeNext( standState.get() );
  return standState;
}

PlayerState::PTR PlayerStateFactory::createPunchL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchL");
      currentCharacter.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_L, sf::seconds(1.0f), 
                                        enter, none, none );
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchM");
      currentCharacter.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_M,
                                        sf::seconds(1.4f), 
                                        enter, none, none );
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchR");
      currentCharacter.loseStamina(20.0f);
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_R,
                                        sf::seconds(1.0f), 
                                        enter, none, none);
  return punchState;
}


PlayerState::PTR PlayerStateFactory::createDodgeL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeL");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_L,
                                        sf::seconds(0.3f), 
                                        enter, none, none );
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeM");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_M,
                                        sf::seconds(0.3f), 
                                        enter, none, none);
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeR");
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_R, 
                                        sf::seconds(0.3f), 
                                        enter, none, none);
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createStroke()
{
  auto enter = Function::create([this](){
      std::cout << "entering STROKE" << std::endl;
      currentCharacter.vulnerable = false;
      currentCharacter.receivedHits++;
      currentCharacter.loseHealth(40);
      anim->playAnimation("stroke");
    });
  auto exit = Function::create([this](){
      currentCharacter.vulnerable = true;
    });
  auto state = PlayerState::create(PlayerState::STROKE,
                                   sf::seconds(0.3f), 
                                   enter, none, exit);
  return state;
}

PlayerState::PTR PlayerStateFactory::createKO()
{
 auto enter = Function::create([this](){
      anim->playAnimation("KO");
    });
 auto state = PlayerState::create(PlayerState::KO,
                                   sf::seconds(1.5f), 
                                   enter, none, none);
  return state;
}

PlayerState::PTR PlayerStateFactory::createRaising()
{
 auto enter = Function::create([this](){
      anim->playAnimation("raising");
    });
 auto state = PlayerState::create(PlayerState::RAISING, 
                                   sf::seconds(1.6f), 
                                   enter, none, none);
  return state;
}

PlayerState::PTR PlayerStateFactory::createHappy()
{
 auto enter = Function::create([this](){
     anim->playAnimation("happy", true);
    });
 auto state = PlayerState::create(PlayerState::HAPPY,
                                   sf::seconds(3.1f), 
                                   enter, none, none);
  return state;
}

PlayerState::PTR PlayerStateFactory::createStun()
{
 auto enter = Function::create([this](){
     anim->playAnimation("stun", true);
    });
 auto state = PlayerState::create(PlayerState::STUN,
                                   sf::seconds(1.6f), 
                                   enter, none, none );
  return state;
}

PlayerState::PTR PlayerStateFactory::createBreathing()
{
 auto enter = Function::create([this](){
     anim->playAnimation("breathing", true);
    });
 auto state = PlayerState::create(PlayerState::BREATHING,
                                   sf::seconds(1.6f), 
                                   enter, none, none);
  return state;
}

