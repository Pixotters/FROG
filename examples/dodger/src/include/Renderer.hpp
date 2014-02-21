#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer{

  //// attributes ////
protected:
  sf::RenderTexture * m_texture;

  //// operations ////
public:
  Renderer();

  virtual ~Renderer();

  /*
    returns the renderer's texture, the "area" where it draws
   */
  sf::RenderTexture * getTexture() const;

  /*
    cleans all pixels of the texture to the given color
   */
  virtual void clear(const sf::Color& = sf::Color::Black);

  /*
    display the texture
   */
  virtual void display();

};

#endif
