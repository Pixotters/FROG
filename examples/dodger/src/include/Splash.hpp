#ifndef SPLASH_HPP
#define SPLASH_HPP

#include <FROG/Core/AppInfo.hpp>
#include <FROG/Core/GameObject.hpp>
#include <FROG/Rendering/Scene.hpp>

class Splash : virtual public frog::Scene
{

private:
  unsigned short splashIndex;
  frog::GameObject::PTR splash;
  frog::GameObject::PTR text;

public:
  Splash(frog::AppInfo&);
  virtual ~Splash();
  virtual void enter();
  virtual void postupdate();

private:
  void manage();
  void updateImage();
  void updateText();

};

#endif
