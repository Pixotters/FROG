#include "Splash.hpp"
#include "MainMenu.hpp"

#include <FROG/Rendering/Sprite.hpp>
#include <FROG/Rendering/TextSprite.hpp>

#define SPLASH_TIME 3.0f
#define SPLASH_NUMBER 2

using namespace frog;

Splash::Splash(AppInfo& appinfo)
  : Scene(appinfo), 
    splashIndex(0),
    splash(new GameObject),
    text(new GameObject)
{
}

Splash::~Splash()
{
}

void Splash::enter()
{
  appInfo.clock.restart();
  // setting up image
  auto& first_splash = defaultTextureManager.get("SPLASHSCREEN_0");
  splash->addComponent( Sprite::create(first_splash) , 
                      "RENDERING");
  unsigned int two = 2;
  auto orig = static_cast<sf::Vector2f>(first_splash.getSize() / two);
  splash->transform->setOrigin( orig );
  auto pos = static_cast<sf::Vector2f>(appInfo.window.getSize() / two );
  splash->transform->setPosition( pos );
  addObject(splash);
  // setting up text
  auto& font = defaultFontManager.get("SPLASH_FONT");
  auto ts = TextSprite::create("Pixotters  present", font);
  text->addComponent( ts, "RENDERING");
  ts->centerText();
  text->transform->setPosition(pos.x, pos.y + orig.y + 15);
  addObject(text);
}

void Splash::postupdate()
{
  if (appInfo.clock.getElapsedTime().asSeconds() > SPLASH_TIME)
    {
      manage();
      appInfo.clock.restart();
    }
}

void Splash::manage()
{
  splashIndex++;
  if (splashIndex < SPLASH_NUMBER)
    {
      updateImage();
      updateText();
    }else
    {
      appInfo.stateManager.change(new MainMenu(appInfo) );
    }
}

void Splash::updateImage()
{
  std::ostringstream oss;
  oss << "SPLASHSCREEN_"<< splashIndex;
  auto& newsplash = defaultTextureManager.get( oss.str() );
  oss.flush();
  unsigned int two = 2;
  auto orig = static_cast<sf::Vector2f>(newsplash.getSize() / two );
  splash->transform->setOrigin( orig );
  splash->getComponent<Sprite>("RENDERING")->setTexture(newsplash);
}

void Splash::updateText()
{
  auto textcomp = text->getComponent<TextSprite>("RENDERING"); 
  switch (splashIndex)
    {
    case 0:
      textcomp->setText("Pixotters  present");
      break;

    case 1:
      textcomp->setText("Developped with FROG - \nFor Really Outstanding Games");
      break;

    default:
      textcomp->setText("");
      break;
    }
  textcomp->centerText();
}
