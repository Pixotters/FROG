#include "Match.hpp"
#include "ChangeState.hpp"
#include "CharacterPlayed.hpp"
#include "PlayerMachine.hpp"
#include "PlayerState.hpp"
#include "PlayerStateFactory.hpp"

#include <FROG/Collision/BoxCollider.hpp>
#include <FROG/Control.hpp>
#include <FROG/Rendering/Animator.hpp>
#include <FROG/Rendering/Sprite.hpp>
#include <FROG/Rendering/TextSprite.hpp>

#define STAMINA_GAIN 10.0f

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
    ring(new GameObject() ),
    health1(new GameObject() ),
    stamina1(new GameObject() ),
    health2(new GameObject() ),
    stamina2(new GameObject() ),
    time(new GameObject() )
{
  std::cout << "loading match " << std::endl;
  loadFromFile("assets/scenes/match.xml");
  std::cout << "loaded match " << std::endl;
  player1->addProperty<CharacterPlayed>("character", new CharacterPlayed(ch1) );
  player2->addProperty<CharacterPlayed>("character", new CharacterPlayed(ch2) );
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
  addObject(ring);
  // setting up clock
  auto& time_font = defaultFontManager.get("SCORE_FONT");
  time->addComponent( TextSprite::create("0 0 0", time_font, 40),
                      "RENDERING");
  time->getComponent<TextSprite>("RENDERING")->centerText( );
  time->transform->setPosition(400, 30);
  time->transform->layer = 5;
  addObject(time);
  //
  setGUI();
  setPlayers();
  setControls();
  timer.restart();
}

void Match::setGUI()
{
  auto& gui_img = defaultTextureManager.get("GUI");
  // setting up frame of gauges
  auto time_frame = GameObject::create();
  time_frame->addComponent(Sprite::create(gui_img, sf::IntRect(0,46,128,64) ),
                           "RENDERING");
  time_frame->transform->setOrigin(64, 32);
  time_frame->transform->setPosition(400, 40);
  time_frame->transform->layer = 4;
  addObject(time_frame);
  auto hl = GameObject::create();
  auto health_frame1 = Sprite::create(gui_img, sf::IntRect(0, 0, 155, 15) );
  auto health_frame2 = Sprite::create(gui_img, sf::IntRect(0, 0, 155, 15) );
  hl->addComponent(health_frame1, "RENDERING");
  hl->transform->layer = 4;
  auto hr = GameObject::create();
  hr->addComponent(health_frame2, "RENDERING");
  hr->transform->setPosition(800-155, 0);
  hr->transform->layer = 4;
  auto stamina_frame1 = Sprite::create(gui_img, sf::IntRect(0, 32, 104, 8) );
  auto stamina_frame2 = Sprite::create(gui_img, sf::IntRect(0, 32, 104, 8) );
  auto sl = GameObject::create();
  sl->addComponent(stamina_frame1, "RENDERING");
  sl->transform->setPosition(0, 25);
  sl->transform->layer = 4;
  auto sr = GameObject::create();
  sr->addComponent(stamina_frame2, "RENDERING");
  sr->transform->setPosition(800-104, 25);
  sr->transform->layer = 4;
  addObject(hl);
  addObject(hr);
  addObject(sl);
  addObject(sr);
  /// 
  health1->transform->layer = 5;
  health1->addComponent(Sprite::create(gui_img, sf::IntRect(0, 16, 155, 16) ), 
                        "RENDERING");
  health2->transform->layer = 5;
  health2->addComponent(Sprite::create(gui_img, sf::IntRect(0, 16, 155, 16) ), 
                        "RENDERING");
  health2->transform->setPosition(800-155, 0);
  addObject(health1);
  addObject(health2);
  stamina1->transform->layer = 5;
  stamina1->addComponent(Sprite::create(gui_img, sf::IntRect(2, 40, 100, 6) ), 
                        "RENDERING");
  stamina1->transform->setPosition(2, 25);
  stamina2->transform->layer = 5;
  stamina2->addComponent(Sprite::create(gui_img, sf::IntRect(2, 40, 100, 6) ), 
                        "RENDERING");
  stamina2->transform->setPosition(800-102, 25);
  addObject(stamina1);
  addObject(stamina2);
 
}

void Match::setPlayers()
{  
  // setting up player1
  float y_backs = 550;
  float y_fronts = 350;
  float x_left = 150;
  float x_right = 650;
  auto& img1_back = defaultTextureManager.get("AVRAGE_BACK");
  auto& sprt_back = defaultSpritesheetManager.get("BACK");
  player1->transform->setPosition( sf::Vector2f(x_left-10, y_backs) );
  player1->transform->layer = 3;
  auto anim1 = Animator<std::string>::create(appInfo.deltaTime, 
                                             sprt_back, 
                                             img1_back);
  anim1->setDefaultAnimation("stand");  
  anim1->playAnimation("stand", true);  
  player1->addComponent(anim1, "RENDERING" );
  // setting up mirror1  
  auto& img1_front = defaultTextureManager.get("AVRAGE_FRONT");
  auto& sprt_front = defaultSpritesheetManager.get("FRONT");
  mirror1->transform->setPosition( sf::Vector2f(x_right+10, y_fronts) );
  mirror1->transform->layer = 2;
  auto anim1m = Animator<std::string>::create(appInfo.deltaTime,
                                              sprt_front, 
                                              img1_front);
  anim1m->setDefaultAnimation("stand");  
  anim1m->playAnimation("stand", true);  
  mirror1->addComponent(anim1m, "RENDERING");
  // setting up player2
  auto& img2_back = defaultTextureManager.get("SDARD_BACK");
  player2->transform->setPosition( sf::Vector2f(x_right, y_backs) );
  player2->transform->layer = 3;
  auto anim2 = Animator<std::string>::create(appInfo.deltaTime,
                                             sprt_back, 
                                             img2_back);
  anim2->setDefaultAnimation("stand");  
  anim2->playAnimation("stand", true);  
  player2->addComponent(anim2, "RENDERING" );
  // setting up mirror2
  mirror2->transform->setPosition( sf::Vector2f(x_left, y_fronts) );
  mirror2->transform->layer = 2;
  auto& img2_front = defaultTextureManager.get("SDARD_FRONT");
  auto anim2m = Animator<std::string>::create(appInfo.deltaTime,
                                              sprt_front, 
                                              img2_front);
  anim2m->setDefaultAnimation("stand");  
  anim2m->playAnimation("stand", true);  
  mirror2->addComponent(anim2m, "RENDERING");
  //  
  addObject(mirror1);  
  addObject(mirror2);  
  addObject(player1);  
  addObject(player2); 
}

void Match::setControls()
{
  // creating state changer factories
  auto fsm1 = PlayerMachine::create();
  player1->addComponent(fsm1, "FSM");
  auto fsm2 = PlayerMachine::create();
  player2->addComponent(fsm2, "FSM");
  auto factory1 = PlayerStateFactory::create(player1,
                                             mirror1,
                                             player2);
  auto factory2 = PlayerStateFactory::create(player2,
                                             mirror2,
                                             player1);
  // setting controls for P1
  ChangeState::create(fsm1, factory1, PlayerState::STAND)->execute();
  auto ctrl1 = ControlComponent::create(appInfo.eventList);
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::A, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::PUNCH_L) );
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::Z, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::PUNCH_M) );
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::E, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::PUNCH_R) );
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::Q, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::DODGE_L) );
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::S, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::DODGE_M) );
  ctrl1->bind(KeyboardButton::create(sf::Keyboard::D, Trigger::PRESSED),
              ChangeState::create(fsm1, factory1, PlayerState::DODGE_R) );
  player1->addComponent(ctrl1, "CONTROL");
  // setting controls for P2
  ChangeState::create(fsm2, factory2, PlayerState::STAND)->execute();
  auto ctrl2 = ControlComponent::create(appInfo.eventList);
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::I, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::PUNCH_L) );
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::O, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::PUNCH_M) );
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::P, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::PUNCH_R) );
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::K, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::DODGE_L) );
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::L, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::DODGE_M) );
  ctrl2->bind(KeyboardButton::create(sf::Keyboard::M, Trigger::PRESSED),
              ChangeState::create(fsm2, factory2, PlayerState::DODGE_R) );
  player2->addComponent(ctrl2, "CONTROL");
  
}

void Match::postupdate()
{
  unsigned time_left = matchInfo.timePerRound-timer.getElapsedTime().asSeconds();
  if (time_left <= 0)
    {
      // TODO next round
    }
  else
    {
      auto sta_gain = STAMINA_GAIN * appInfo.deltaTime.asSeconds();
      player1->getProperty<CharacterPlayed>("character").gainStamina(sta_gain);  
      player2->getProperty<CharacterPlayed>("character").gainStamina(sta_gain);
    }
  updateGUI(time_left);
}

void Match::updateGUI(unsigned time_left)
{
  auto& char1 = player1->getProperty<CharacterPlayed>("character");
  auto& char2 = player2->getProperty<CharacterPlayed>("character");
  // stamina
  auto st1_pcent = ( char1.currentStamina / (float)char1.getStamina() ) * 100;
  stamina1->getComponent<Sprite>("RENDERING")
    ->setClip(sf::IntRect(2, 40, st1_pcent, 6) );
  //
  auto st2_pcent = ( char2.currentStamina / (float)char2.getStamina() ) * 100;
  auto st2_sprite = stamina2->getComponent<Sprite>("RENDERING");
  st2_sprite->setClip(sf::IntRect(2, 40, st2_pcent, 6) );
  auto decS = (int)100-(int)st2_pcent;
  st2_sprite->setPosition(800-102+decS, 25);
  // health
  auto h1_pcent = ( char1.currentHealth / (float)char1.getHealth() ) * 150;
  health1->getComponent<Sprite>("RENDERING")
    ->setClip(sf::IntRect(0, 16, 3+h1_pcent, 16) );
  //
  auto h2_pcent = ( char2.currentHealth / (float)char2.getHealth() ) * 150;
  auto h2_sprite = health2->getComponent<Sprite>("RENDERING");
  h2_sprite->setClip(sf::IntRect(0, 16, 3+h2_pcent, 16) );
  auto decH = (int)150-(int)h2_pcent;
  h2_sprite->setPosition(800-155+decH, 0);
  // timer
  std::ostringstream time_string;
  time_string << time_left/100 << " " << time_left%100/10 << " " << time_left%10;
  time->getComponent<TextSprite>("RENDERING")->setText( time_string.str() );
  time_string.flush();
}
