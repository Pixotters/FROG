#include "Options.hpp"

#include <FROG/Rendering/TextSprite.hpp>

using namespace frog;

Options::Options(frog::AppInfo& a)
  : Scene(a)
{
  loadFromFile("assets/scenes/menu.xml");
}

Options::~Options()
{

}

void Options::enter()
{
  auto& font = defaultFontManager.get("MSG_FONT");
  auto label_rounds = GameObject::create();
  label_rounds->addComponent(TextSprite::create("Rounds", font) ,
                             "RENDERING");
  addObject(label_rounds);
}

void Options::postupdate()
{
  collisionManager.update();
}
