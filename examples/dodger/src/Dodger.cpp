#include "FROG/App.hpp"

#include "Level.hpp"
#include "Start.hpp"

#include <iostream>

int main()
{
  frog::App d("Dodger - A Sample game developed with FROG");
  std::cout << "Starting game" << std::endl;
  Level * l = new Level(d.appInfo);
  d.start( l );
  delete l;
  std::cout << "Game Exited without any problem" << std::endl;
}
