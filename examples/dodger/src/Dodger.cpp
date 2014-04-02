#include "FROG/App.hpp"
#include "FROG/Random.hpp"

#include "Level.hpp"

#include <iostream>

using namespace frog;

int main()
{
  std::cout << "Starting game" << std::endl;
  App::instance()->init(new Level() );
  Random::init();
  std::cout << "Initialization successful. Running..." << std::endl;
  App::instance()->run();
  std::cout << "Stopping game..." << std::endl;
  App::instance()->exit();
  std::cout << "Ended game properly" << std::endl;


}
