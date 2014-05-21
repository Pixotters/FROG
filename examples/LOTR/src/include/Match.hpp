#ifndef MATCH_HPP
#define MATCH_HPP

#include <FROG/Rendering/Scene.hpp>

#include "MatchInfo.hpp"
#include "Character.hpp"
#include "CharacterPlayed.hpp"
#include "PlayerMachine.hpp"

class Match : virtual public frog::Scene
{

private:
  MatchInfo matchInfo;
  frog::GameObject::PTR player1;
  frog::GameObject::PTR mirror1;
  frog::GameObject::PTR player2;
  frog::GameObject::PTR mirror2;
  frog::GameObject::PTR ring;  
  frog::GameObject::PTR health1;
  frog::GameObject::PTR stamina1;
  frog::GameObject::PTR health2;
  frog::GameObject::PTR stamina2;
  frog::GameObject::PTR time;
  sf::Clock timer;
  float stamina_loss;
  float health_loss;
  float stamina_gain;
  unsigned short hitsToStun;

public:
  Match(frog::AppInfo& appInfo, 
        const MatchInfo& matchInfo, 
        const Character& character1,
        const Character& character2);
  virtual ~Match();
  virtual void enter();
  void setGUI();
  void setControls();
  void setPlayers();
  virtual void postupdate();
  void updateGUI(unsigned time_left,
                 CharacterPlayed& char1,
                 CharacterPlayed& char2);
  void checkStamina(CharacterPlayed& _char, frog::GameObject::PTR& player);
  void gainStamina(CharacterPlayed& char1, CharacterPlayed& char2);
  void gainHealth(CharacterPlayed& char1, float amount);
  void loseStamina(CharacterPlayed& _char);
  bool isKO(CharacterPlayed& _char);
  void loseHealth(CharacterPlayed& _char);
  bool checkHit(PlayerState::ID id1,
                PlayerState::ID id2);
  void tryHit(PlayerState::ID id1,
              frog::GameObject::PTR& o2);
  void makeHappy(frog::GameObject::PTR);
  bool isTKO(CharacterPlayed& _char);
  void checkEnd();


};

#endif
