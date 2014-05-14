#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <FROG/Core/Scene.hpp>

class MainMenu : virtual public frog::Scene
{

public:
  MainMenu(AppInfo&);
  virtual ~MainMenu();

};

#endif
