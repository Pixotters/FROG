#include "FROG/Core/App.hpp"

#include "Level.hpp"
#include "Start.hpp"

#include <iostream>

int main()
{
  frog::App d("Dodger - A Sample game developed with FROG");
  std::cout << "Starting game" << std::endl;
  Start * s = new Start(d.appInfo);
  d.start( s );
  std::cout << "Game Exited without any problem" << std::endl;
}
