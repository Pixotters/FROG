#include "FROG/App.hpp"
#include "FROG/Random.hpp"

#include "Level.hpp"

#include <iostream>

using namespace frog;

class Dodger : virtual public App
{
};

int main()
{
  Dodger d;
  std::cout << "Starting game" << std::endl;
  d.init(  new Level( *(d.m_appInfo) )  );
  Random::init();
  std::cout << "Initialization successful. Running..." << std::endl;
  d.loop();
  std::cout << "Stopping game..." << std::endl;
  d.exit();
  std::cout << "Ended game properly" << std::endl;


}
