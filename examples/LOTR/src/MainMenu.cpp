#include "MainMenu.hpp"

#include "GUI_Button.hpp"
#include "MouseMover.hpp"
#include "Options.hpp"
// REMOVE
#include "Match.hpp"
#include "MatchInfo.hpp"
#include "Character.hpp"
//

#include <FROG/Collision/BoxCollider.hpp>
#include <FROG/Control/Function.hpp>
#include <FROG/Rendering/Sprite.hpp>

#include <iostream>

using namespace frog;

MainMenu::MainMenu(AppInfo& appinfo)
  : Scene(appinfo)
{
  // TODO do this properly
  loadFromFile("assets/scenes/menu.xml");
}

MainMenu::~MainMenu()
{
}

void MainMenu::enter()
{
  auto& font = defaultFontManager.get("MSG_FONT");
  ButtonUI::PTR bui(new ButtonUI("test", font, sf::Vector2f(200, 100) ) );
  bui->setBackground(sf::Color::Red);
  // TODO : move after "Options"
  MatchInfo ma;
  ma.type = MatchInfo::KO;
  ma.roundsNumber = 3;
  ma.strengthModifier = 0;
  ma.fatigueModifier = 0;
  ma.timePerRound = 90;
  ma.TKO = true;
  Character c1("a");
  Character c2("b");
  //
  auto fun = Function::create([this, ma, c1, c2](){
      //      appInfo.stateManager.change( new Options(appInfo) );
      appInfo.stateManager.change( new Match(appInfo, ma, c1, c2) );
    });
  GameObject::PTR button( new Button(appInfo.eventList, bui, fun) );
  button->transform->setPosition(400, 300);
  addObject(button);
  collisionMngr.addObject(button);
  // setting up cursor
  auto cursor = GameObject::create();
  auto& cursor_tex = defaultTextureManager.get("CURSOR");
  cursor->addComponent(new Sprite(cursor_tex), "RENDERING" );
  cursor->addComponent(new MouseMover(), "CONTROL");
  cursor->addComponent(BoxCollider::create(sf::Vector2f(20, 20) ), 
                       "COLLIDER");
  cursor->transform->setOrigin( sf::Vector2f(10, 10) );
  cursor->addProperty<std::string>("type", "cursor");
  addObject(cursor);
  collisionMngr.addObject(cursor);
}

void MainMenu::postupdate()
{
  collisionMngr.update();
}
