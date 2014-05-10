#ifndef START_HPP
#define START_HPP

#include "FROG/AssetManager.hpp"
#include "FROG/Scene.hpp"

#include "FontID.hpp"

class Start: virtual public frog::Scene
{
private:
  frog::AssetManager<FONT_ID, sf::Font> m_fontManager;

public:
  Start(frog::AppInfo&);
  virtual ~Start();
  virtual void enter();

};

#endif
