#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <FROG/Collision/PairManager.hpp>
#include <FROG/Rendering/Scene.hpp>

#include "Options.hpp"

class Options : virtual public frog::Scene
{

private:
  frog::PairManager collisionManager;

public:
  Options(frog::AppInfo&);
  virtual ~Options();
  virtual void enter();
  virtual void postupdate();


};

#endif
