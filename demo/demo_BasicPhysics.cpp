#include <SFML/System/Vector2.hpp>
#include <cmath>
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
                 virtual public sap::Collisionable {};

class Walls : virtual public TestBody {

    /* dummy class to make circles stay in the sreen */
public:

    int xMin, xMax, yMin, yMax;

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
           const sf::Color& color = sf::Color::White)
        : TestBody(), m_radius(rad){
        sf::Shape * m_sprite = new sf::CircleShape(rad);
        m_sprite->setFillColor(color);
        addComponent(new render::RenderingComponent(m_sprite ) );
    };

    virtual ~Circle();

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
        for(unsigned int it = 0; it < n; it++)
            {
                unsigned int x = Random::get(0, 800);
                unsigned int y = Random::get(0, 600);
                addCircle(x, y, new Circle() );
            }
        m_collider = new sap::LSAP(new AcMan() );  
    }

    virtual ~Demo(){}
    void addCircle(const unsigned int& x, const unsigned int& y, Circle * c){
        Transform& t = c->getTransform();
        t.setPosition(x, y);
        addObject(c);
    };

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
