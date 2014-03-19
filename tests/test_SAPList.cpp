#define BOOST_TEST_MODULE Test_SAPList
#include <boost/test/unit_test.hpp>

#include <typeinfo>

/* make everything public for testing */
#define private public
#define protected public
#include "../src/SAPList.hpp"

/* 
 * USER DEFINED CLASSES
 * - ActionManagerTester implements ActionManager
 * - CollisionableTester implements Collisionable
 * - 2 empty classes derived from CollisionableTester
 */

class CollisionableTester : virtual public Collisionable {
public:
    int x, y, w, h;
    virtual int getXMin() { return this->x; }
    virtual int getYMin() { return this->y; }
    virtual int getXMax() { return this->x + this->w; }
    virtual int getYMax() { return this->y + this->h; }

    CollisionableTester() : CollisionableTester(0, 0, 0, 0) {}
    CollisionableTester(int i1, int i2, int i3, int i4) :
        x(i1), y(i2), w(i3), h(i4) {}
    ~CollisionableTester() {}
};

class Collisionable_type1 : virtual public CollisionableTester {
public:
    Collisionable_type1() : CollisionableTester(0, 0, 0, 0) {};
};

class Collisionable_type2 : virtual public CollisionableTester {
public:
    Collisionable_type2() : CollisionableTester(10, 11, 12, 13) {}
};

class ActionManagerTester : virtual public ActionManager {
public:

    int status;

    /* (type1, typ2) */
    virtual void onCollision(Collisionable_type1 * o1,
                             Collisionable_type2 * o2)
    { this->status = 24; }
    virtual void onSeparation(Collisionable_type1 * o1,
                              Collisionable_type2 * o2) 
    { this->status = -24; }

    /* (type1, not type2) */
    virtual void onCollision(Collisionable_type1 * o1,
                     Collisionable * o2)
    { this->status = 42; }
    virtual void onSeparation(Collisionable_type1 * o1,
                              Collisionable * o2)
    { this->status = -42; }

    /* (not type1, any type) */
    virtual void onCollision(Collisionable * o1,
                             Collisionable * o2)
    {
        Collisionable_type1 * c1 = dynamic_cast<Collisionable_type1*>(o1);
        Collisionable_type2 * c2 = dynamic_cast<Collisionable_type2*>(o2);

        if (c1)
            if (c2)
                this->onCollision (c1, c2);
            else
                this->onCollision (c1, o2);
        else
            this->status  = 1;
    }

    virtual void onSeparation(Collisionable * o1,
                              Collisionable * o2)
    {
        Collisionable_type1 * c1 = dynamic_cast<Collisionable_type1*>(o1);
        Collisionable_type2 * c2 = dynamic_cast<Collisionable_type2*>(o2);

        if (c1)
            if (c2)
                this->onSeparation (c1, c2);
            else
                this->onSeparation (c1, o2);
        else
            this->status  = -1;
    }

    ActionManagerTester() : status(0) {}
};

/*
 * FIXTURE
 * SAP fixture using previous classes
 */

struct SAPListFixture {
    ActionManagerTester am;
    SAPList cm;
    Collisionable_type1 o1;
    Collisionable_type2 o2;
    SAPListFixture () : cm(&am) {}
};

/*
 * TESTS
 */


BOOST_AUTO_TEST_SUITE( SAPList_constructors )

BOOST_FIXTURE_TEST_CASE ( Collisionable_type1_constructor, SAPListFixture ) {

    BOOST_REQUIRE_EQUAL( o1.x, 0 );
    BOOST_REQUIRE_EQUAL( o1.y, 0 );
    BOOST_REQUIRE_EQUAL( o1.w, 0 );
    BOOST_REQUIRE_EQUAL( o1.h, 0 );

}

BOOST_FIXTURE_TEST_CASE ( Collisionable_type2_constructor, SAPListFixture ) {

    BOOST_REQUIRE_EQUAL( o2.x, 10 );
    BOOST_REQUIRE_EQUAL( o2.y, 11 );
    BOOST_REQUIRE_EQUAL( o2.w, 12 );
    BOOST_REQUIRE_EQUAL( o2.h, 13 );

}

BOOST_FIXTURE_TEST_CASE( SAP_defaultContructor, SAPListFixture )
{
    BOOST_REQUIRE_EQUAL( cm.xAxis->next->prev, cm.xAxis );
    BOOST_REQUIRE_EQUAL( cm.yAxis->next->prev, cm.yAxis );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( SAPList_functions )

BOOST_FIXTURE_TEST_CASE( SAP_mk_AABB, SAPListFixture )
{

    auto test = [](SAPList::AABB * aabb,
                   int xMin, int yMin,
                   int xMax, int yMax,
                   Collisionable * obj)
        { BOOST_CHECK_EQUAL( aabb->min[0]->value, xMin );
          BOOST_CHECK_EQUAL( aabb->min[1]->value, yMin );
          BOOST_CHECK_EQUAL( aabb->max[0]->value, xMax );
          BOOST_CHECK_EQUAL( aabb->max[1]->value, yMax );
          BOOST_CHECK_EQUAL( aabb->owner, obj); };

    SAPList::AABB * aabb1 = cm.mk_AABB(&o1);
    SAPList::AABB * aabb2 = cm.mk_AABB(&o2);

    test(aabb1, 0, 0, 0, 0, &o1);
    test(aabb2, 10, 11, 10 + 12, 11 + 13, &o2);

    delete aabb1;
    delete aabb2;
    
}

BOOST_FIXTURE_TEST_CASE ( SAP_swap, SAPListFixture )
{
    SAPList::EndPoint
        p1(NULL, 0, false),
        p2(NULL, 10, false),
        * null = static_cast<SAPList::EndPoint*> (NULL);

    p1.next = &p2;
    p2.prev = &p1;

    BOOST_CHECK_EQUAL ( p1.prev, null );
    BOOST_CHECK_EQUAL ( p1.next, &p2 );
    BOOST_CHECK_EQUAL ( p2.prev, &p1 );
    BOOST_CHECK_EQUAL ( p2.next, null );
    
    cm.swap(&p1, &p2);

    BOOST_CHECK_EQUAL( p2.prev, null );
    BOOST_CHECK_EQUAL( p2.next, &p1 );
    BOOST_CHECK_EQUAL( p1.prev, &p2 );
    BOOST_CHECK_EQUAL( p1.next, null );

}

BOOST_FIXTURE_TEST_CASE ( SAP_updateAxis, SAPListFixture )
{
    SAPList::EndPoint
        min (NULL, INT_MIN, false),
        p1 (NULL, 0, false),
        p2 (NULL, 10, false),
        p3 (NULL, 20, false),
        p4 (NULL, 30, false),
        max (NULL, INT_MAX, false);

    auto check_order = [](SAPList::EndPoint*p1,
                   SAPList::EndPoint*p2,
                   SAPList::EndPoint*p3,
                   SAPList::EndPoint*p4,
                   SAPList::EndPoint*p5,
                   SAPList::EndPoint*p6) {

        BOOST_CHECK_EQUAL( p1->next, p2 );
        BOOST_CHECK_EQUAL( p2->prev, p1 );
        BOOST_CHECK_EQUAL( p2->next, p3 );
        BOOST_CHECK_EQUAL( p3->prev, p2 );
        BOOST_CHECK_EQUAL( p3->next, p4 );
        BOOST_CHECK_EQUAL( p4->prev, p3 );
        BOOST_CHECK_EQUAL( p4->next, p5 );
        BOOST_CHECK_EQUAL( p5->prev, p4 );
        BOOST_CHECK_EQUAL( p5->next, p6 );
        BOOST_CHECK_EQUAL( p6->prev, p5 );

    };

    /* Initialization */

    min.next = &p1;
    p1.prev = &min;
    p1.next = &p2;
    p2.prev = &p1;
    p2.next = &p3;
    p3.prev = &p2;
    p3.next = &p4;
    p4.prev = &p3;
    p4.next = &max;
    max.prev = &p4;
    
    /* Tests */

    cm.updateAxis(&p2, &p3);
    check_order(&min, &p1, &p2, &p3, &p4, &max);

    p2.value = 25;
    p3.value = 35;
    cm.updateAxis(&p2, &p3);
    check_order(&min, &p1, &p2, &p4, &p3, &max);
    
    p2.value = 10;
    p3.value = 20;
    cm.updateAxis(&p2, &p3);
    check_order(&min, &p1, &p2, &p3, &p4, &max);

}

BOOST_FIXTURE_TEST_CASE( SAP_addObject, SAPListFixture )
{
    
    auto test = [](SAPList::EndPoint * pt,
                   Collisionable * obj, int val, bool isMin)
        { BOOST_CHECK_EQUAL(pt->owner->owner, obj);
          BOOST_CHECK_EQUAL(pt->value, val);
          BOOST_CHECK_EQUAL(pt->isMin, isMin); };
    
    SAPList::EndPoint
        
        * xMin = cm.xAxis,
        * xMax = cm.xAxis->next,
      
        * yMin = cm.yAxis,
        * yMax = cm.yAxis->next;

    cm.addObject(&o1);

    test(xMin->next, &o1, 0, true);
    test(xMax->prev, &o1, 0, false);
    test(yMin->next, &o1, 0, true);
    test(yMax->prev, &o1, 0, false);

    cm.addObject(&o2);

    test(xMin->next, &o1, 0, true);
    test(xMin->next->next, &o1, 0, false);
    test(xMin->next->next->next, &o2, 10, true);
    test(xMin->next->next->next->next, &o2, (10 + 12), false);

    test(xMax->prev, &o2, (10 + 12), false);
    test(xMax->prev->prev, &o2, 10, true);
    test(xMax->prev->prev->prev, &o1, 0, false);
    test(xMax->prev->prev->prev->prev, &o1, 0, true);

    test(yMin->next, &o1, 0, true);
    test(yMin->next->next, &o1, 0, false);
    test(yMin->next->next->next, &o2, 11, true);
    test(yMin->next->next->next->next, &o2, (11 + 13), false);

    test(yMax->prev, &o2, (11 + 13), false);
    test(yMax->prev->prev, &o2, 11, true);
    test(yMax->prev->prev->prev, &o1, 0, false);
    test(yMax->prev->prev->prev->prev, &o1, 0, true);

    }

BOOST_FIXTURE_TEST_CASE ( SAP_collisionCheck, SAPListFixture )
{
    SAPList::AABB
        a(0, 0, 10, 10, NULL),
        b(5, 5, 15, 15, NULL);

    BOOST_CHECK ( cm.partialCollisionCheck (a, b, 0) );
    BOOST_CHECK ( cm.partialCollisionCheck (a, b, 1) );
    BOOST_CHECK ( cm.collisionCheck (a, b) );
    BOOST_CHECK ( cm.collisionCheck (b, a) );
}

BOOST_FIXTURE_TEST_CASE( SAP_actionManager, SAPListFixture )
{

    BOOST_CHECK_EQUAL (am.status, 0); // default is zero

    cm.addObject(&o1);
    cm.addObject(&o2);

    SAPList::AABB* aabb = static_cast<SAPList::AABB*>(o1.boundingBox);
    aabb->max[0]->value = 11; // o2 xMin is at 10
    aabb->max[1]->value = 12; // o2 yMin is at 11
    cm.updateObject(&o1);
    BOOST_CHECK_EQUAL (am.status, 24); // 24 on (typ1, typ2) collision

    aabb->max[0]->value = 0; // o2 xMin is at 10
    aabb->max[1]->value = 0; // o2 yMin is at 11
    cm.updateObject(&o1);
    BOOST_CHECK_EQUAL (am.status, -24); // -24 on (typ1, typ2) separation

    Collisionable_type1 tmp;
    cm.addObject(&tmp);
    aabb = static_cast<SAPList::AABB*>(tmp.boundingBox);

    aabb->max[0]->value = 2;
    aabb->max[1]->value = 2;
    cm.updateObject(&tmp);
    BOOST_CHECK_EQUAL (am.status, 42); // 42 on (typ1, typ1) collision

    aabb->min[0]->value = 1;
    aabb->min[1]->value = 1;
    cm.updateObject(&tmp);
    BOOST_CHECK_EQUAL (am.status, -42); // -42 on (typ1, typ1) separation

}

BOOST_AUTO_TEST_SUITE_END()
