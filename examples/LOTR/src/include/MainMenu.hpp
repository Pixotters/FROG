#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <FROG/Collision/PairManager.hpp>
#include <FROG/Rendering/Scene.hpp>

class MainMenu : virtual public frog::Scene
{

private:
  frog::PairManager collisionMngr;

public:
  MainMenu(frog::AppInfo&);
  virtual ~MainMenu();
  virtual void enter();
  virtual void postupdate();

};

#endif
