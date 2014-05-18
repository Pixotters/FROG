#include "Match.hpp"
#include "CharacterPlayed.hpp"
#include "PlayerMachine.hpp"
#include "PlayerState.hpp"
#include "MouseMover.hpp"
#include "MovePlayer.hpp"

#include <FROG/Collision/BoxCollider.hpp>
#include <FROG/Control.hpp>
#include <FROG/Rendering/Animator.hpp>
#include <FROG/Rendering/Sprite.hpp>

using namespace frog;

Match::Match(AppInfo& a, 
             const MatchInfo& m,
             const Character& ch1,
             const Character& ch2)
  : Scene(a), matchInfo(m),
    player1(new GameObject() ),
    mirror1(new GameObject() ),
    player2(new GameObject() ),
    mirror2(new GameObject() ),
    ring(new GameObject() )
{
  std::cout << "loading match " << std::endl;
  loadFromFile("assets/scenes/match.xml");
  std::cout << "loaded match " << std::endl;
  //player1->addProperty<CharacterPlayed>("character", new CharacterPlayed(ch1) );
  //player2->addProperty<CharacterPlayed>("character", new CharacterPlayed(ch2) );

  std::cout << "match created " << std::endl;

}

Match::~Match()
{

}

void Match::enter()
{
  // setting up ring 
  auto& ringimg = defaultTextureManager.get("RING");
  ring->addComponent(Sprite::create(ringimg), "RENDERING");
  ring->transform->layer = 1;
  // setting up player1
  float y_backs = 550;
  float y_fronts = 350;
  float x_left = 150;
  float x_right = 450;
  auto& img1_back = defaultTextureManager.get("AVRAGE_BACK");
  auto& sprt_back = defaultSpritesheetManager.get("BACK");
  player1->transform->setPosition( sf::Vector2f(x_left, y_backs) );
  player1->transform->layer = 3;
  auto anim1 = Animator<std::string>::create(sprt_back, img1_back);
  anim1->setDefaultAnimation("stand");  
  anim1->playAnimation("stand", true);  
  player1->addComponent(anim1, "RENDERING" );
  setControls();
  // setting up mirror1  
  auto& img1_front = defaultTextureManager.get("AVRAGE_FRONT");
  mirror1->transform->setPosition( sf::Vector2f(x_right, y_fronts) );
  mirror1->addComponent(Animator<std::string>::create(sprt_front, img1_front) );
  // adding objects
  addObject(ring);
  addObject(player1);  
  addObject(mirror1);  
  addObject(player2);  
}


void Match::setControls()
{
 auto ctrl = ControlComponent::create(appInfo.eventList);
  // REMOVE
  std::shared_ptr<Command> moveleft(new MovePlayer(player1, -32, 0, appInfo) );
  std::shared_ptr<Command> moveright(new MovePlayer(player1, 32, 0, appInfo) );
  std::shared_ptr<Command> moveup(new MovePlayer(player1, 0, -32, appInfo) );
  std::shared_ptr<Command> movedown(new MovePlayer(player1, 0, 32, appInfo) );
  auto qkey = KeyboardButton::create(sf::Keyboard::Q);
  auto dkey = KeyboardButton::create(sf::Keyboard::D);
  auto zkey = KeyboardButton::create(sf::Keyboard::Z);
  auto skey = KeyboardButton::create(sf::Keyboard::S);
  ctrl->bind(qkey, moveleft );    
  ctrl->bind(dkey, moveright );
  ctrl->bind(zkey, moveup );  
  ctrl->bind(skey,  movedown );
 
  //
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
