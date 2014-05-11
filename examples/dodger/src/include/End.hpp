#ifndef END_HPP
#define END_HPP

#include "FROG/Scene.hpp"
#include "FROG/AppInfo.hpp"

#include "FontID.hpp"

#include <fstream>
#include <iostream>
#include <vector>

class End : virtual public frog::Scene
{

private:
  unsigned int score;
  frog::AssetManager<FONT_ID, sf::Font> m_fontManager;

public:
  End(frog::AppInfo&, unsigned int);
  virtual ~End();
  virtual void enter();

private:
  std::vector<unsigned int> getScores(std::ifstream&) const;
  bool checkBest(std::vector<unsigned int>&, 
                 unsigned int) const;

};

#endif
