#include "BasicPhysics.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath.h>

class Walls : virtual public PhysicBody {

  int xMin, xMax, yMin, yMax;

  /* dummy class to make circles stay in the sreen */
public:

  Walls (int xi, int xa, int yi, int ya) :
    xMin(xi), xMax(xa), yMin(yi), yMax(ya) {}
  ~Walls () {}

  virtual sf::Vector2f getNormal(int x, int y) {

    sf::Vector2f v(0,0);

    if (x <= xMin) {
      v += sf::Vector2f(0, 1);
    } else if (x >= xMax) {
      v += sf::Vector2f(0, -1);
    }

    if (y <= yMin) {
      v += sf::Vector2f(1, 0);
    } else if (y >= Ymax) {
      v += sf::Vector2f(-1, 0);
    }
  }

protected:
  /* do not react when force applied */
  virtual void applyForce(const sf::Vector2f & f) {}

};

class Circle : virtual public PhysicBody {

private:
  int x, y;
  int r;

public:

  Circle (int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
  ~Circle () {}

  virtual sf::Vector2f getNormal(int x, int y) {

    float _x = x - this->x;
    float _y = y - this->y;
    float len = sqrt(pow(_x, 2) + pow(_y, 2));

    return sf::Vector2f ( _x / len, _y / len);
        
  }
};



////////////////////////////////////////////////////////////////////////





class Demo : virtual public Scene
{

public:
  Demo(const unsigned int& n) : Scene(){
    for(unsigned int it = 0; it < n; it++)
      {
        unsigned int x = Random::get(0, 800);
        unsigned int y = Random::get(0, 600);
        addCircle(x, y, new GCircle() );
      }
    m_collider = new sap::LSAP(am);  
  }

  virtual ~Demo(){}
  void addCircle(const unsigned int& x, const unsigned int& y, GCircle * c){
    Transform * t = c->getTransform();
    t->setPosition(x, y);
    addObject(c);
  };
};

class GCircle : virtual public GameObject
{

private:
  sf::CircleShape m_sprite;

public:
  GCircle(const float& rad = 32,
          const sf::Color& c = sf::Color::White){
    m_sprite.setRadius(rad);
    m_sprite.setColor(c);
    addComponent<RenderingComponent>(m_sprite);
  };
  virtual ~GCircle();
};

/////////////////////////:

int main(int argc, char ** argv)
{
  int n = 7;
  if(argc > 1)
    n = atoi(argv[1]);
  App::instance()->init(new Demo(n) );
  Random::init();
  App::instance()->run();
  App::instance()->exit();
}

/* TODO:
 * - Implements a simple CollisionManager
 * - Add Walls
 * - Add Circles with initial random movement
 * - Render scene and relax
 */

