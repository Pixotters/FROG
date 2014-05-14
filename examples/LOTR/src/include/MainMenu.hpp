#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <FROG/Rendering/Scene.hpp>

class MainMenu : virtual public frog::Scene
{

public:
  MainMenu(frog::AppInfo&);
  virtual ~MainMenu();

};

#endif
