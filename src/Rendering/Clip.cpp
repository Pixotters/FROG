#include "FROG/Rendering/Clip.hpp"

namespace frog{

  Clip::Clip(int x, int y, 
             unsigned w, unsigned h,
             int hx, int hy)
  {
    rectangle.left = x;
    rectangle.top = y;
    rectangle.width = w;
    rectangle.height = h;
    hotpoint.x = hx;
    hotpoint.y = hy;
  }

  Clip::Clip(const Clip& other)
    : rectangle(other.rectangle), hotpoint(other.hotpoint)
  {

  }


  Clip::~Clip()
  {
  }

}
