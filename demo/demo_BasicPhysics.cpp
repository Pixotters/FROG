#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "FROG/Physics/BasicPhysics.hpp"
#include "FROG/Scene.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Collision/ActionManager.hpp"

using namespace frog;

class TestBody : virtual public PhysicBody, virtual public sap::Collisionable {};

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

protected:
    /* do not react when force applied */
    virtual void applyForce(const sf::Vector2f & f) {}

};

class Circle : virtual public TestBody {

public:

    int x, y;
    int r;

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

class BaPhy : virtual public BasicPhysics {};

class AcMan : virtual public sap::ActionManager {

    /* Yep, this is ugly, but ActionManager needs to be improved */

public:

    BaPhy buck;

    /* FIXME: Dummy collision position is center of first cicle */

    virtual void onCollision(TestBody * b1, TestBody * b2) {
        /* Collision between circle + something else */
        Circle * c1 = dynamic_cast<Circle*>(b1);

        if (Circle * c2 = dynamic_cast<Circle*>(b2)) {
            buck.reaction(c1, c2, c1->x, c1->y);
        } else if (Walls * w = dynamic_cast<Walls*>(b2)) {
            buck.reaction(c1, w, c1->x, c1->y);
        }
    }

    virtual void onSeparation(TestBody * b1, TestBody * b2) {
        /* Separation: do nothing except if a Circle try to run out Walls */
        Circle * c = dynamic_cast<Circle*>(b1);
        Walls * w = dynamic_cast<Walls*>(b2);
        if (c != NULL && w != NULL) {
            buck.reaction(c, w, c->x, c->y);
        }
    }

};
