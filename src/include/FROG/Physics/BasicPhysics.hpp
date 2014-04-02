#ifndef BASICPHYSICS_HPP
#define BASICPHYSICS_HPP 1

#include <SFML/System/Vector2.hpp>

class PhysicBody {

    friend class BasicPhysics;

protected:

    sf::Vector2f force;

public:
    void applyForce(const sf::Vector2f & f) {
        force += f;        
    }

    PhysicBody(float x = 0, float y = 0) : force(x, y) {}

    virtual ~PhysicBody() {}
};

class BasicPhysics {
public:
    void reaction(PhysicBody * b1, PhysicBody * b2){
        /* Apply force to each other + force reaction */
        sf::Vector2f tmp = b1->force;
        b1->applyForce(b2->force - b1->force);
        b2->applyForce(tmp - b2->force);
    }
};

#endif
