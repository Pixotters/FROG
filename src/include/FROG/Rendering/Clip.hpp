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
    
    Clip(const int& x = 0, const int& y = 0, 
         const unsigned& w = 0, const unsigned& h = 0,
         const int& hx = 0, const int& hy = 0);
    virtual ~Clip();
    
  };

}

#endif
