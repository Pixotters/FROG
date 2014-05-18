#ifndef MATCH_HPP
#define MATCH_HPP

#include <FROG/Rendering/Scene.hpp>

#include "MatchInfo.hpp"
#include "Character.hpp"

class Match : virtual public frog::Scene
{

private:
  MatchInfo matchInfo;
  frog::GameObject::PTR player1;
  frog::GameObject::PTR mirror1;
  frog::GameObject::PTR player2;
  frog::GameObject::PTR mirror2;
  frog::GameObject::PTR ring;  

public:
  Match(frog::AppInfo& appInfo, 
        const MatchInfo& matchInfo, 
        const Character& character1,
        const Character& character2);
  virtual ~Match();
  virtual void enter();
  void setControls();

};

#endif
