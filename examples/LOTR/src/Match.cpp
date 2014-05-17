#include "Match.hpp"
#include "CharacterPlayed.hpp"
#include "PlayerMachine.hpp"
#include "PlayerState.hpp"

#include <FROG/Control.hpp>
#include <FROG/Rendering/Animator.hpp>

using namespace frog;

Match::Match(AppInfo& a, 
             const MatchInfo& m,
             const Character& ch1,
             const Character& ch2)
  : Scene(a), matchInfo(m)
{
  player1->addProperty<CharacterPlayed>("character", 
                                        new CharacterPlayed(ch1) );
  player2->addProperty<CharacterPlayed>("character", 
                                        new CharacterPlayed(ch2) );

}

Match::~Match()
{

}

void Match::enter()
{
  // setting up player1
  PlayerMachine::PTR fsm1(new PlayerMachine() );
  auto& img1_front = defaultTextureManager.get("AVRAGE_FRONT");
  auto& img1_back = defaultTextureManager.get("AVRAGE_BACK");
  auto& sprt_front = defaultSpritesheetManager.get("FRONT");
  auto& sprt_back = defaultSpritesheetManager.get("BACK");
  player1->addComponent(Animator<std::string>::create(sprt_front, img1_front),
                        "RENDERING");
  auto stand_enter = []( PlayerMachine::PTR m, GameObject::PTR o){
    auto anim = o->getComponent<Animator<std::string>>("RENDERING");
    anim->playAnimation("stand");
    m->resetCount();
  };
  fsm1->push(new PlayerState(fsm1, player1, stand_enter) );
  player1->addComponent(fsm1, "FSM");
  auto ctrl = ControlComponent::create(appInfo.eventList);
  ctrl->bind(KeyboardButton::create(sf::Keyboard::A, Trigger::PRESSED),
             Function::create( [fsm1](){
                 //                 fsm1->change(); 
               } ) 
             );
  player1->addComponent(ctrl, "CONTROL");
}
/*
auto stand_enter = []( PlayerMachine& m, GameObject::PTR o){
  auto anim = o->getComponent<Animator<std::string>>("RENDERING");
  anim->playAnimation("stand");
  m.resetCount();
};
PlayerState::PTR PlayerMachine::STAND( new PlayerState(stand_enter) );

auto punchL_enter = []( PlayerMachine& m, GameObject::PTR o){
  auto anim = o->getComponent<Animator<std::string>>("RENDERING");
  anim->playAnimation("punchL", false);
  m.resetCount();
};
auto punchL_update = [](PlayerMachine& m, GameObject::PTR o){
  if (m.frame == 5)
    std::cout << "hit " << std::endl;
};
PlayerState::PTR PlayerMachine::PUNCH(new PlayerState(punchL_enter, punchL_update) );

*/
