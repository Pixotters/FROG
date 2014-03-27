#include "Main/App.hpp"
#include "Main/Random.hpp"

#include <iostream>

using namespace frog;

int main()
{
  std::cout << "Starting game" << std::endl;
  App::instance()->init();
  Random::init();
  std::cout << "Initialization successful. Running..." << std::endl;
  App::instance()->run();
  std::cout << "Stopping game..." << std::endl;
  App::instance()->exit();
  std::cout << "Ended game properly" << std::endl;


}
