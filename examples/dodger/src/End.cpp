#include "End.hpp"

#include "FROG/Control/ControlComponent.hpp"
#include "FROG/Rendering/TextSprite.hpp"

#include <SFML/Graphics/Font.hpp>

#include <string>
#include <sstream>

#include <iostream> // TODO remove

#define SCOREFILE "scores"

using namespace frog;

End::End(AppInfo& a, unsigned int s)
  : Scene(a), score(s)
{
  if (not loadFromFile("assets/scenes/end.xml") )
    throw std::runtime_error("Could not load EndState");
}

End::~End()
{
}

void End::enter()
{
  // retireving scores from a file
  std::ifstream scorefile_in;
  scorefile_in.open( SCOREFILE );
  auto scores = getScores(scorefile_in);
  scorefile_in.close();
  // if score performed is in TOP 10, rewrite it 
  if (checkBest(scores, score) )
    {
      std::ofstream scorefile_out;
      scorefile_out.open(SCOREFILE);
      for (auto s : scores)
        {
          scorefile_out << s << std::endl;
        }
        scorefile_out.flush();
        scorefile_out.close();
    }
  // creating the string to display
  std::ostringstream oss;
  oss << "You scored " << score << " points." << std::endl << std::endl;
  oss << "TOP 10 : " << std::endl;
  for (auto s : scores)
    {
      oss << s << std::endl;
    }
  // creating the object displaying the text
  GameObject::PTR_GameObject msg(new GameObject() );
  sf::Font& font = defaultFontManager.get("MSG_FONT");
  msg->addComponent(new TextSprite(oss.str(), font ),
                    "RENDERING");
  addObject(msg);
  oss.flush();
}

std::vector<unsigned int> End::getScores(std::ifstream& scorefile) const
{
  if (scorefile.fail() )
    {
      throw std::runtime_error("Could not open score file.");
    }
  std::vector<unsigned int> scores;
  while (not scorefile.eof() )
    {
      unsigned int s;
      scorefile >> s;
      scores.push_back(s);
    }
  scorefile.close();
  return scores;
}

bool End::checkBest(std::vector<unsigned int>& scores, 
                    unsigned int score) const
{
  bool sort = false;
  for (auto s: scores)
    {
      if (score > s)
        {
          sort = true;
          break;
        }       
    }
  if (sort)
    {
      scores.push_back(score);
      std::function<bool(unsigned int a, unsigned int b)> comp
        = [](unsigned int a, unsigned int b){ return a > b; };
      std::sort(scores.begin(), scores.end(), comp);
      scores.resize(10);
    }
  return sort;
}


