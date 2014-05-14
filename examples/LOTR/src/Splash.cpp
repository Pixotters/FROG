#include "Splash.hpp"

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
  appInfo.clock.reset();
  auto first_splash = defaultTextureManager.get("SPLASHSCREEN_1");
  splash.addComponent( Sprite::create(first_splash) , 
                      "RENDERING");
  addObject(splash);
}

void Splash::postupdate()
{
  if (appInfo.clock.getElapsedTime().asSeconds() > SPLASH_TIME)
    {
      changeSplash();
      appInfo.clock.reset();
    }
}

void Splash::manage()
{
  splashIndex++;
  if (splashIndex < SPLASH_NUMBER)
    {
      std::ostringstream oss;
      oss << "SPLASHSCREEN_"<< splashIndex;
      auto newsplash = defaultTextureManager.get( oss.str() );
      oss.flush();
      splash.getComponent<Sprite>("RENDERING").setTexture(newsplash);
    }else
    {
      appInfo.stateManager.change(new MainMenu(appInfo) );
    }
}

