#include "Splash.hpp"

#include <FROG/Core/App.hpp>

int main()
{
  frog::App lotr("Lordz of the ring");
  std::shared_ptr<Splash> splash( new Splash(lotr.appInfo) );
  splash->loadFromFile("assets/scenes/splash.xml");
  lotr.start( splash.get() );
}
