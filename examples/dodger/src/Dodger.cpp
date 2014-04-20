#include "FROG/App.hpp"
#include "FROG/Random.hpp"

#include "Level.hpp"

#include <iostream>

using namespace frog;
/*
class Dodger : public App
{
public:
  Dodger():App(){
  std::cerr << "Dodger CTOR: APPInfos are at " << m_appInfo << std::endl;
  }
  virtual ~Dodger(){};
};
*/
int main()
{
  App d;
  std::cout << "Starting game" << std::endl;
  AppInfo& i = d.getAppInfo();
  int dec = 0x000000000060;
  //  std::cerr << "Dodger : APPInfos are at " << &i << "-" << (&i)+dec << "/" << i+dec << std::endl;
  //  std::cerr << "Dodger : Window is at " << &d.m_appInfo->window << std::endl;
  d.init(  new Level( i )  );
  Random::init();
  std::cout << "Initialization successful. Running..." << std::endl;
  d.loop();
  std::cout << "Stopping game..." << std::endl;
  d.exit();
  std::cout << "Ended game properly" << std::endl;


}
