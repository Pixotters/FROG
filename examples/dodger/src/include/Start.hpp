#ifndef START_HPP
#define START_HPP

#include "FROG/Core/AssetManager.hpp"
#include "FROG/Rendering/Scene.hpp"

class Start: virtual public frog::Scene
{

public:
  Start(frog::AppInfo&);
  virtual ~Start();
  virtual void enter();

};

#endif
