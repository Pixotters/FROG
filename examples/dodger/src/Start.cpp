#include "Start.hpp"

#include "Level.hpp"

#include "FROG/Command.hpp"
#include "FROG/Function.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Rendering/TextSprite.hpp"
#include "FROG/Control/AnyKey.hpp"
#include "FROG/Control/AnyJoystickButton.hpp"
#include "FROG/Control/ControlComponent.hpp"

using namespace frog;

Start::Start(AppInfo& a)
  : Scene(a)
{
  //  m_fontManager.loadFromFile("assets/fonts/Hyperspace_Bold.ttf", GUI_FONT);
  loadFromFile("assets/scenes/start.xml");
}

Start::~Start()
{
}

void Start::enter()
{
  GameObject::PTR t( new GameObject() );
  std::string text = "Objective\n\nEat donuts to get score. \n";
  text += "Everytime you eat 10 donuts in a row, your multiplier increases. \n";
  text += "\nAvoid red squares : when you get hit, you lose your multiplier. \n";
  text += "You also lose a life. When your 3 lives are lost, the game is over.";
  text += "\n\nPress any key";
  //  sf::Font& font = m_fontManager.get(GUI_FONT);
  sf::Font& font = defaultFontManager.get("GUI_FONT");
  t->addComponent(new TextSprite(text, font, 20), 
                  "RENDERING" );
  std::shared_ptr<ControlComponent> ctrl(new ControlComponent(appInfo.eventList) );
  std::shared_ptr<Command> next(new Function([this](){
        this->appInfo.stateManager.change(new Level(*this) ); } ) );
  ctrl->bind(AnyKey::create(), next);
  ctrl->bind(AnyJoystickButton::create(), next);
  t->addComponent(ctrl, "CONTROL");
  addObject(t);
}
