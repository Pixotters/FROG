#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <FROG/Collision/LSAP.hpp>
#include <FROG/Rendering/Scene.hpp>

class MainMenu : virtual public frog::Scene
{

private:
  frog::LSAP collisionMngr;

public:
  MainMenu(frog::AppInfo&);
  virtual ~MainMenu();
  virtual void enter();

};

#endif
