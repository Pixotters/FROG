#include "PlayerStateFactory.hpp"

#include "Match.hpp"

#include <FROG/Control/Function.hpp>

#include <algorithm>
#include <iostream> // TODO remove

using namespace frog;


static auto none = Function::create([](){});

PlayerStateFactory::PlayerStateFactory(Match * _match,
                                       GameObject::PTR& p1, 
                                       GameObject::PTR& p2, 
                                       GameObject::PTR& m1)
  : match(_match),
    current(p1),
    other(p2),
    currentCharacter( p1->getProperty<CharacterPlayed>("character") ),
    anim(p1->getComponent<Animator<std::string>>("RENDERING") ),
    mirror(m1->getComponent<Animator<std::string>>("RENDERING") )
{
}

PlayerStateFactory::~PlayerStateFactory()
{
}

PlayerStateFactory::PTR PlayerStateFactory::create(Match * _match, 
                                                   GameObject::PTR& p1, 
                                                   GameObject::PTR& p2,
                                                   GameObject::PTR& m1)
{
  return PTR( new PlayerStateFactory(_match, p1, p2, m1) );
}

PlayerState::PTR PlayerStateFactory::get(PlayerState::ID id)
{
  auto find = states.find(id);
  if (find != states.end() )
    {
      return find->second;
    }else
    {
      auto st = createState(id);
      states.emplace(id, st);
      return st;
    }
}

PlayerState::PTR PlayerStateFactory::createState(PlayerState::ID id)
{
  PlayerState::PTR ptr;
  switch(id)
    {
    case PlayerState::STAND:
      ptr = createStand();
      break;
    case PlayerState::PUNCH_L:
      ptr = createPunchL();
      break;
    case PlayerState::PUNCH_M:
      ptr = createPunchM();
      break;
    case PlayerState::PUNCH_R:
      ptr = createPunchR();
      break;
    case PlayerState::DODGE_L:
      ptr = createDodgeL();
      break;
    case PlayerState::DODGE_M:
      ptr = createDodgeM();
      break;
    case PlayerState::DODGE_R:
      ptr = createDodgeR();
      break;
    case PlayerState::STROKE:
      ptr = createStroke();
      break;
    case PlayerState::KO:
      ptr = createKO();
      break;
    case PlayerState::RAISING:
      ptr = createRaising();
      break;
    case PlayerState::HAPPY:
      ptr = createHappy();
      break;
    case PlayerState::STUN:
      ptr = createStun();
      break;
    case PlayerState::BREATHING:
      ptr = createBreathing();
      break;
    default:
      ptr = createStand();
      break;
    }
  states.emplace(id, ptr);
  return ptr;
}

PlayerState::PTR PlayerStateFactory::createStand()
{
  auto enter = Function::create([this](){
      currentCharacter.gainsStamina = true;
      anim->playAnimation("stand");
      mirror->playAnimation("stand");
    });
  auto update = Function::create([this](){      
      match->checkStamina(currentCharacter, current);
    });
  auto standState = PlayerState::create(PlayerState::STAND,
                                        sf::seconds(0.6f), 
                                        enter, update, none);
  standState->changeNext( standState.get() );
  return standState;
}

PlayerState::PTR PlayerStateFactory::createPunchL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchL");
      mirror->playAnimation("punchL");
      currentCharacter.gainsStamina = false;
      match->loseStamina(currentCharacter);
    });
  auto exit = Function::create([this](){
      //      match->checkStamina(current, other);
      //      currentCharacter.gainsStamina = true;
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_L, sf::seconds(1.0f), 
                                        enter, none, exit,
                                        get(PlayerState::STAND).get() );
  auto strike = Function::create([this](){
      match->tryHit(PlayerState::PUNCH_L, other);
    });
  punchState->addCommand(sf::seconds(0.4f), strike);
  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchM");
      mirror->playAnimation("punchM");
      currentCharacter.gainsStamina = false;
      match->loseStamina(currentCharacter);
    });
  auto exit = Function::create([this](){
      //      currentCharacter.gainsStamina = true;
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_M,
                                        sf::seconds(1.4f), 
                                        enter, none, exit,
                                        get(PlayerState::STAND).get() );
  auto strike = Function::create([this](){
      match->tryHit(PlayerState::PUNCH_M, other);
    });
  punchState->addCommand(sf::seconds(0.5f), strike);

  return punchState;
}

PlayerState::PTR PlayerStateFactory::createPunchR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("punchR");
      mirror->playAnimation("punchR");
      currentCharacter.gainsStamina = false;
      match->loseStamina(currentCharacter);
    });
  auto exit = Function::create([this](){
      //      match->checkStamina(current, other);
      //      currentCharacter.gainsStamina = true;
    });
  auto punchState = PlayerState::create(PlayerState::PUNCH_R,
                                        sf::seconds(1.0f), 
                                        enter, none, exit,
                                        get(PlayerState::STAND).get() );
  auto strike = Function::create([this](){
      match->tryHit(PlayerState::PUNCH_R, other);
    });
  punchState->addCommand(sf::seconds(0.4f), strike);
  return punchState;
}


PlayerState::PTR PlayerStateFactory::createDodgeL()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeL");      
      mirror->playAnimation("dodgeL");      
      currentCharacter.gainsStamina = false;
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_L,
                                        sf::seconds(0.3f), 
                                        enter, none, none,
                                        get(PlayerState::STAND).get() );
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeM()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeM");
      mirror->playAnimation("dodgeM");
      currentCharacter.gainsStamina = false;
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_M,
                                        sf::seconds(0.3f), 
                                        enter, none, none,
                                        get(PlayerState::STAND).get());
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createDodgeR()
{
  auto enter = Function::create([this](){
      anim->playAnimation("dodgeR");
      mirror->playAnimation("dodgeR");
      currentCharacter.gainsStamina = false;
    });
  auto dodgeState = PlayerState::create(PlayerState::DODGE_R, 
                                        sf::seconds(0.3f), 
                                        enter, none, none,
                                        get(PlayerState::STAND).get() );
  return dodgeState;
}

PlayerState::PTR PlayerStateFactory::createStroke()
{
  auto enter = Function::create([this](){
      currentCharacter.gainsStamina = true;
      currentCharacter.vulnerable = false;
      anim->playAnimation("stroke");
      mirror->playAnimation("stroke");
    });
  auto exit = Function::create([this](){
      currentCharacter.vulnerable = true;
    });
  auto state = PlayerState::create(PlayerState::STROKE,
                                   sf::seconds(0.3f), 
                                   enter, none, exit, 
                                   get(PlayerState::STAND).get() );
  return state;
}

PlayerState::PTR PlayerStateFactory::createKO()
{
  auto enter = Function::create([this](){
      currentCharacter.gainsStamina = true;      
      currentCharacter.vulnerable = false;
      anim->playAnimation("KO");
      mirror->playAnimation("KO");
      match->makeHappy(other);
    });
  auto state = PlayerState::create(PlayerState::KO,
                                   sf::seconds(1.5f), 
                                   enter, none, none,
                                   get(PlayerState::RAISING).get() );
  return state;
}

PlayerState::PTR PlayerStateFactory::createRaising()
{
  auto enter = Function::create([this](){
      anim->playAnimation("raising");
      mirror->playAnimation("raising");
    });
  auto update = Function::create([this](){
      float amount = 1.0f - (0.2f * (float)(currentCharacter.KOs) );
      if (amount <= 0.2f)
        amount = 2.0f;
      float targetHealth = ((float)currentCharacter.getHealth() ) * amount;
      float step = targetHealth / 1.6f;
      match->gainHealth(currentCharacter, std::min(targetHealth, step ) );
    });
  auto exit = Function::create([this](){
      currentCharacter.vulnerable = true;
    });
  auto state = PlayerState::create(PlayerState::RAISING, 
                                   sf::seconds(1.6f), 
                                   enter, update, exit,
                                   get(PlayerState::STAND).get() );
  return state;
}

PlayerState::PTR PlayerStateFactory::createHappy()
{
  auto enter = Function::create([this](){
      currentCharacter.gainsStamina = true;
      anim->playAnimation("happy", true);
      mirror->playAnimation("happy", true);
    });
  auto state = PlayerState::create(PlayerState::HAPPY,
                                   sf::seconds(3.1f), 
                                   enter, none, none,
                                   get(PlayerState::STAND).get() );
  return state;
}

PlayerState::PTR PlayerStateFactory::createStun()
{
  auto enter = Function::create([this](){      
      currentCharacter.gainsStamina = true;
      anim->playAnimation("stun", true);
      mirror->playAnimation("stun", true);
    });
  auto state = PlayerState::create(PlayerState::STUN,
                                   sf::seconds(1.6f), 
                                   enter, none, none,
                                   get(PlayerState::STAND).get()  );
  return state;
}

PlayerState::PTR PlayerStateFactory::createBreathing()
{
  auto enter = Function::create([this](){
      anim->playAnimation("breathing", true);
      mirror->playAnimation("breathing", true);
      currentCharacter.gainsStamina = true;
    });
  auto state = PlayerState::create(PlayerState::BREATHING,
                                   sf::seconds(1.6f), 
                                   enter, none, none,
                                   get(PlayerState::STAND).get() );
  return state;
}

