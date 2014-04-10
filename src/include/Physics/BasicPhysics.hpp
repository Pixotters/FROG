#ifndef BASICPHYSICS_HPP
#define BASICPHYSICS_HPP 1

#include <SFML/System/Vector2.hpp>

/**
 * This first physic engine only deals with basic collisions
 * (i.e. rotations are not supported yet)
 */

class PhysicBody {

    /**
     * This class assumes that we are able to give coordinate of collision
     * point.
     */

    friend class BasicPhysics;

protected:

    sf::Vector2f force;


    /* FIXME:
     * making it virtual could be interesting if we want some objects
     * to act different, but we want this? */
    virtual void applyForce(const sf::Vector2f & f) {
        force += f;
    }

    /**
     * Gives the normal vector (collision reponse)
     * @param x X axis coordinate of collision
     * @param y Y axis coordinate of collision
     */
    virtual sf::Vector2f getNormal(int x, int y) = 0;

public:

    PhysicBody(float x = 0, float y = 0) : force(x, y) {}

    virtual ~PhysicBody() {}
};

class BasicPhysics {

protected:

    sf::Vector2f dotProduct (const sf::Vector2f & v1, const sf::Vector2f & v2) {
        return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
    }

    // Projection of vector v on axis a
    // see http://www.metanetsoftware.com/technique/tutorialA.html#appendixA
    sf::Vector2f projection (const sf::Vector2f & v, const sf::Vector2f & a) {
        auto tmp = (v.x*a.x + v.y*a.y) / (v.x*v.x + v.y*v.y);
        return sf::Vector2f(tmp * v.x, tmp * v.y);
    }

public:

    /**
     * Compute and apply reaction when two bodies collide. 
     * The order arguments are passed does not matter.
     * @param b1 first body colliding
     * @param b2 second body colliding
     * @param x X axis coordinate of collision point
     * @param y Y axis coordinate of collision point
     */

    void reaction(PhysicBody * b1, PhysicBody * b2, int x, int y){


        // see http://elancev.name/oliver/2D%20polygon.htm#tut4
        // ELASTICITY should be replaced by a object property
#define ELASTICITY 1.0f

        sf::Vector2f n1 = b1->getNormal(x, y);
        sf::Vector2f n2 = b2->getNormal(x, y);

        /* Apply force to each other + force reaction */
        b1->applyForce( - dotProduct
                        (((1.0f + ELASTICITY) * projection (b1->force, n2)),
                         n2));
        b2->applyForce( - dotProduct
                        (((1.0f + ELASTICITY) * projection (b2->force, n1)),
                         n1));
    }
};

#endif
