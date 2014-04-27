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
  //  std::cerr << "Dodger : APPInfos are at " << &i << "-" << (&i)+dec << "/" << i+dec << std::endl;
  //  std::cerr << "Dodger : Window is at " << &d.m_appInfo->window << std::endl;
  std::cerr << "creating level" << std::endl;
  Scene * level = new Level(i);
  std::cerr << "loading file" << std::endl;
  if( level->loadFromFile("assets/scenes/main_scene/main_scene.xml") )
    d.start(  level  );

}
