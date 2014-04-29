#ifndef FROG_CLIP_HPP
#define FROG_CLIP_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>


namespace frog{

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
