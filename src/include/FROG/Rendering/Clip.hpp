#ifndef FROG_CLIP_HPP
#define FROG_CLIP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>


namespace frog{

  /*!
   * Clips are parts of a Spritesheet. They are defined by a rectangle telling 
   * which prt of an image it should be extracted from, and a hotpoint, 
   * representing a gap between position of the owner, and position where image 
   * should be displayed. 
   */
  struct Clip{
    
    sf::IntRect rectangle;
    sf::Vector2i hotpoint;
    
    Clip(int x = 0, int y = 0, 
         unsigned w = 0, unsigned h = 0,
         int hx = 0, int hy = 0);
    Clip(const Clip&);
    virtual ~Clip();
    
  };

}

#endif
