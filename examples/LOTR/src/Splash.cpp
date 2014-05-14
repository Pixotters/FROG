#include "Splash.hpp"
#include "MainMenu.hpp"

#include <FROG/Rendering/Sprite.hpp>

#define SPLASH_TIME 1.5f
#define SPLASH_NUMBER 2

using namespace frog;

Splash::Splash(AppInfo& appinfo)
  : Scene(appinfo), 
    splashIndex(0),
    splash(new GameObject)
{
}

Splash::~Splash()
{
}

void Splash::enter()
{
  appInfo.clock.restart();
  auto& first_splash = defaultTextureManager.get("SPLASHSCREEN_0");
  splash->addComponent( Sprite::create(first_splash) , 
                      "RENDERING");
  unsigned int two = 2;
  auto orig = static_cast<sf::Vector2f>(first_splash.getSize() / two);
  splash->transform->setOrigin( orig );
  auto pos = static_cast<sf::Vector2f>(appInfo.window.getSize() / two );
  splash->transform->setPosition( pos );
  addObject(splash);
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
      std::ostringstream oss;
      oss << "SPLASHSCREEN_"<< splashIndex;
      auto& newsplash = defaultTextureManager.get( oss.str() );
      oss.flush();
      unsigned int two = 2;
      auto orig = static_cast<sf::Vector2f>(newsplash.getSize() / two );
      splash->transform->setOrigin( orig );
      splash->getComponent<Sprite>("RENDERING")->setTexture(newsplash);
    }else
    {
      appInfo.stateManager.change(new MainMenu(appInfo) );
    }
}

