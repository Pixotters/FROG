#ifndef GUI_HPP
#define GUI_HPP

#include "FROG/Core/Component.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>


class GUI : virtual public frog::RenderingComponent
{

protected:
  unsigned short m_lives;
  unsigned int m_score;
  unsigned short m_mult;
  sf::RectangleShape m_background;
  sf::Text m_text;

public:
  GUI(unsigned int w, unsigned int h, sf::Font& font, unsigned int lives);
  virtual ~GUI();
  virtual void draw(sf::RenderTarget&, 
                    sf::RenderStates = sf::RenderStates::Default) const;
  void setScore(unsigned int newscore);
  void setLives(unsigned int newlives);
  void setRow(unsigned short m);
  void update(const frog::ComponentHolder&);

private:
  void updateString();

};

#endif
