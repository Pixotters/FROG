#ifndef GUI_HPP
#define GUI_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>


class GUI : virtual public sf::Drawable,
            virtual public sf::Transformable,
            virtual public frog::Component
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
  void draw(sf::RenderTarget&, 
            sf::RenderStates = sf::RenderStates::Default) const;
  void setScore(unsigned int newscore);
  void setLives(unsigned int newlives);
  void setRow(unsigned short m);
  void update(const frog::ComponentHolder&);

private:
  void updateString();

};

#endif
