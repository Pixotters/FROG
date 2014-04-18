#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include "FROG/App.hpp"
#include "FROG/Random.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Physics/BasicPhysics.hpp"
#include "FROG/Scene.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Collision/ActionManager.hpp"

using namespace frog;

class TestBody : virtual public GameObject,
                 virtual public PhysicBody, 
                 virtual public sap::Collisionable {

public:
  TestBody(const float& x = 1, const float& y = 1)
    : GameObject(), sap::Collisionable(), PhysicBody(x, y)
  {

  force += sf::Vector2f(x, y);
    std::cout << this <<" : "
               << x << "," 
               << y <<
      " + " << force.x << "," << force.y << std::endl;    
  };

  virtual ~TestBody(){};
};

class Walls : virtual public TestBody {

    /* dummy class to make circles stay in the sreen */
public:

    int xMin, xMax, yMin, yMax;

    Walls (int xi, int xa, int yi, int ya) :
      TestBody(), xMin(xi), xMax(xa), yMin(yi), yMax(ya) {
      sf::Shape * m_sprite = new sf::CircleShape(1);
      m_sprite->setFillColor(sf::Color::White);
        addComponent(new render::RenderingComponent(m_sprite ) );
    }

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
        } else if (y >= yMax) {
            v += sf::Vector2f(-1, 0);
        }

        return v;
    }

    virtual int getXMin() const { return xMin; }

    virtual int getYMin() const { return yMin; }

    virtual int getXMax() const { return xMax; }

    virtual int getYMax() const { return yMax; }

protected:
    /* do not react when force applied */
    virtual void applyForce(const sf::Vector2f & f) {}

};

////////////////////////////////////////////////////////////////////////


class Circle : virtual public TestBody
{

private:
    sf::CircleShape * m_sprite;
    float m_radius;

public:
    Circle(const float& rad = 32,
           const sf::Color& color = sf::Color::White,
           const int& vx = 1, const int& vy = 1)
      : TestBody(vx, vy ), m_radius(rad){
        sf::Shape * m_sprite = new sf::CircleShape(rad);
        m_sprite->setFillColor(color);
        addComponent(new render::RenderingComponent(m_sprite ) );
    };

    virtual ~Circle() {}

    virtual sf::Vector2f getNormal(int x, int y) {
        float _x = x - getTransform().getPosition().x;;
        float _y = y - getTransform().getPosition().y;
        float len = sqrt(pow(_x, 2) + pow(_y, 2));
    
        return sf::Vector2f ( _x / len, _y / len);        
    }

    virtual int getXMin() const {
        return getTransform().getPosition().x - m_radius; }

    virtual int getYMin() const {
        return getTransform().getPosition().y - m_radius; }

    virtual int getXMax() const {
        return getTransform().getPosition().x + m_radius; }

    virtual int getYMax() const {
        return getTransform().getPosition().y + m_radius; }

};

/* TODO:
 * - Implements a simple CollisionManager
 * - Add Walls
 * - Add Circles with initial random movement
 * - Render scene and relax
 */

class BaPhy : virtual public BasicPhysics {};

class AcMan : virtual public sap::ActionManager {

    /* Yep, this is ugly, but ActionManager needs to be improved */

public:

    BaPhy buck;

    /* FIXME: Dummy collision position is center of first cicle */
  virtual void onCollision(sap::Collisionable * b1, sap::Collisionable * b2) {
        /* Collision between circle + something else */
        Circle * c1 = dynamic_cast<Circle*>(b1);
        int x = c1->getTransform().getPosition().x;
        int y = c1->getTransform().getPosition().y;
        if (Circle * c2 = dynamic_cast<Circle*>(b2)) {
            buck.reaction(c1, c2, x, y);
        } else if (Walls * w = dynamic_cast<Walls*>(b2)) {
            buck.reaction(c1, w, x, y);
        }
    }

  virtual void onSeparation(sap::Collisionable * b1, sap::Collisionable * b2) {
        /* Separation: do nothing except if a Circle try to run out Walls */
        Circle * c = dynamic_cast<Circle*>(b1);
        Walls * w = dynamic_cast<Walls*>(b2);
        int x = c->getTransform().getPosition().x;
        int y = c->getTransform().getPosition().y;
        if (c != nullptr && w != nullptr) {
            buck.reaction(c, w, x, y);
        }
    }

};


class Demo : virtual public Scene
{

public:
    Demo(const unsigned int& n) : Scene(){
        m_collider = new sap::LSAP(new AcMan() );    
        addWalls(0, 800, 0, 600);
        for(unsigned int it = 0; it < n; it++)
            {
              std::cerr << "adding a circle "<<std::endl;
                unsigned int x = Random::get(410, 480);
                unsigned int y = Random::get(100, 200);
                unsigned int vx = Random::get(1, 10);
                unsigned int vy = Random::get(1, 10);
                std::cout << "x, y : "<<x<<","<<y<<
                  "vx, vy : "<< vx << "," << vy << std::endl;
                addCircle(x, y, new Circle(16, sf::Color::Red, vx, vy) );
                
              std::cerr << "added "<<std::endl;
            }
        
        std::cerr << "declaring collider "<<std::endl;
        std::cerr << "declared collider "<<std::endl;

    }

    virtual ~Demo(){}
    void addCircle(const unsigned int& x, const unsigned int& y, Circle * c){
      std::cerr << "addCircle : 1 "<<std::endl;
        Transform * t = c->getPTransform();      
        std::cerr << "addCircle : 2 "<<std::endl;
        t->setPosition(x, y);
      std::cerr << "addCircle : 3 "<<std::endl;
        addObject(c);
              std::cerr << "addCircle : 4 "<<std::endl;
    };
  void addWalls(const int& x1, const int& y1, const int& x2, const int& y2){
    Walls * w = new Walls(x1, x2, y1, y2);
    std::cout<< "created wall"<<std::endl;
    addObject(w);
    std::cout<< "added wall"<<std::endl;
  };

  virtual void update()
  {
    Scene::update();
    auto end = m_gameObjects.end();
    for(auto it = m_gameObjects.begin(); it != end; it++)
      {
        PhysicBody * pb;            
        if( (pb = dynamic_cast<PhysicBody *>(*it) ) )
          {
            Transform * t = (*it)->getPTransform();
            t->move( pb->getVelocity() );
           std::cerr << *it <<" : "
                      << t->getPosition().x << "," 
                      << t->getPosition().y <<
                      " + " << pb->getVelocity().x << "," << pb->getVelocity().y << std::endl;
          }
      }
  }

};

/////////////////////////:

int main(int argc, char ** argv)
{
    int n = 7;
    if(argc > 1)
        n = atoi(argv[1]);
    std::cerr << n<<" circles"<< std::endl;
    Random::init();
    App::instance()->init(new Demo(n) );
    std::cerr << "App init "<< std::endl;
    App::instance()->run();
    std::cerr << "App exiting "<< std::endl;
    App::instance()->exit();
}
