#include "FROG/App.hpp"

#include "Start.hpp"

#include <iostream>

int main()
{
  frog::App d("Dodger - A Sample game developed with FROG");
  std::cout << "Starting game" << std::endl;
  d.start(  new Start(d.appInfo)  );
  std::cout << "Game Exited without any problem" << std::endl;
}
