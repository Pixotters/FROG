#ifndef SAPLIST_HPP
#define SAPLIST_HPP 1

/**
 * TODO:
 * - Optimize merging isMin boolean into another member
 *   (as a flag)
 * - Using doubly-linked list could waste memory but is easier to implement
 *   than arrays.
 */
struct EndPoint {
    struct AABB * owner;
    int value;
    bool isMin;

    struct EndPoint * prev;
    struct EndPoint * next;
};

struct AABBB {
    /** min/max
     *  - first is x axis
     *  - second is y axis */
    struct EndPoint * min[2];
    struct EndPoint * max[2];
    void * owner;
};

class SAP : public CollisionManager {
   

private:
    /** TODO: use sentinels */
    struct EndPoint * xAxis;
    struct EndPoint * yAxis;
    std::vector pm;

    void swap(struct EndPoint * p1, struct EndPoint * p2) {
        p2->next->prev = p1;
        p1->next = p2->next;
        p1->prev->next = p2;
        p1->prev = p2;
        p2->next = p1;
    }

    bool updateEndPointLeft(struct EndPoint * pt) {
        EndPoint * tmp = pt->prev;
        bool moved = false;
        while (tmp->value < pt->value) {
            moved = true;
            swap(tmp, pt);
            if (pt->isMin && !tmp->isMin) {
                //Remove pair
            } else if (!pt->isMin && tmp->isMin) {
                //Add pair
            }
        }
        return moved;
    }

    bool updateEndPointLeft(struct EndPoint * pt) {
        EndPoint * tmp = pt->prev;
        bool moved = false;
        while (tmp->value > pt->value) {
            moved = true;
            swap(tmp, pt);
            if (pt->isMin && !tmp->isMin) {
                //Add pair
            } else if (!pt->isMin && tmp->isMin) {
                //Remove pair
            }
        }
        return moved;
    }

    void updateAxis(struct EndPoint * min, struct EndPoint * max) {
        updateEndPointLeft(min) || updateEndPointRight(min);
        updateEndPointLeft(max) || updateEndPointRight(max);
    }
    
public:
    void addObject(const & struct AABB) {}
    void updateObject(const & struct AABB) {
        updateAxis(AABB->min[0], AABB->max[0]);
        updateAxis(AABB->min[1], AABB->max[1]);
    }
    void removeObject(const & struct AABB) {}
}

#endif
