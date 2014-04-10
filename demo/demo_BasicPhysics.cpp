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


/* TODO:
 * - Implements a simple CollisionManager
 * - Add Walls
 * - Add Circles with initial random movement
 * - Render scene and relax
 */
