#ifndef START_HPP
#define START_HPP

#include "FROG/AssetManager.hpp"
#include "FROG/Scene.hpp"

class Start: virtual public frog::Scene
{

public:
  Start(frog::AppInfo&);
  virtual ~Start();
  virtual void enter();

};

#endif
