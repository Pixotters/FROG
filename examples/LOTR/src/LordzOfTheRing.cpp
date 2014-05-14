#include "Splash.hpp"

int main()
{
  App lotr("Lordz of the ring");
  std::shared_ptr<Splash> splash( new Splash(lotr.appInfo) );
  splash.loadFromFile("assets/scenes/splash.xml");
  lotr.start(splash);
}
