#ifndef BASICPHYSICS_HPP
#define BASICPHYSICS_HPP 1

#include <iostream>
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

    sf::Vector2f velocity;


    /* FIXME:
     * making it virtual could be interesting if we want some objects
     * to act different, but we want this? */
    virtual void applyForce(const sf::Vector2f & f){
        velocity += f;
    };

public:

    PhysicBody(float x = 0, float y = 0) : velocity(x, y) {}

    virtual ~PhysicBody() {}

    sf::Vector2f getVelocity() const{
        return velocity;
    }
};

class BasicPhysics {

protected:

    float dotProduct (const sf::Vector2f & v1, const sf::Vector2f & v2) {
        return v1.x * v2.x + v1.y * v2.y;
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

    void reaction(PhysicBody * b1, PhysicBody * b2,
                  const sf::Vector2f & normal) {


        // see http://elancev.name/oliver/2D%20polygon.htm#tut4
        // ELASTICITY should be replaced by a object property
        // also, here we assume thant b1 and b2 have the same elasticity
#define ELASTICITY 1.0f

        sf::Vector2f v = b1->velocity - b2->velocity;
        sf::Vector2f n = dotProduct (v, normal) * normal * -(1 + ELASTICITY);

        b1->applyForce (n * 0.5f);
        b2->applyForce (- n * 0.5f);

    }
};

#endif
