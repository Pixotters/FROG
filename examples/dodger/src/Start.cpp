#include "Start.hpp"

#include "Level.hpp"

#include "FROG/Command.hpp"
#include "FROG/Function.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Rendering/TextSprite.hpp"
#include "FROG/Control/AnyKey.hpp"
#include "FROG/Control/ControlComponent.hpp"

using namespace frog;

Start::Start(AppInfo& a)
  : Scene(a)
{
  m_fontManager.loadFromFile("assets/fonts/Hyperspace_Bold.ttf", MSG_FONT);
}

Start::~Start()
{
}

void Start::enter()
{
  GameObject::PTR_GameObject t( new GameObject() );
  std::string text = "Objective\n\nEat donuts to get score. \n";
  text += "Everytime you eat 10 donuts in a row, your multiplier increases. \n";
  text += "\nAvoid red squares : when you get hit, you lose your multiplier. \n";
  text += "You also lose a life. When your 3 lives are lost, the game is over.";
  text += "\n\nPress any key";
  sf::Font& font = m_fontManager.get(MSG_FONT);
  t->addComponent(new TextSprite(text, font, sf::Text::Regular, 20), 
                  "RENDERING" );
  std::shared_ptr<ControlComponent> ctrl(new ControlComponent(appInfo.eventList) );
  std::shared_ptr<Command> next(new Function([this](){
        this->appInfo.stateManager.change(new Level(this->appInfo) ); } ) );
  ctrl->bind(AnyKey::create(), next);
  t->addComponent(ctrl, "CONTROL");
  addObject(t);
}