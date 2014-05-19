#include "FROG/Core/App.hpp"

#include "Splash.hpp"

#include <iostream>

int main()
{
  frog::App d("Dodger - A Sample game developed with FROG");
  std::cout << "Starting game" << std::endl;
  Splash * s = new Splash(d.appInfo);
  if( s->loadFromFile("assets/scenes/splash.xml") )
    d.start( s );
  std::cout << "Game Exited without any problem" << std::endl;
}
