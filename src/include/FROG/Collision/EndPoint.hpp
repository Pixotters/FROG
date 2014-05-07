#ifndef FROG_ENDPOINT_HPP
#define FROG_ENDPOINT_HPP

namespace frog{

  class AABB;

  class EndPoint {

    /**
     * TODO:
     * - Optimize merging isMin boolean into another member
     *   (as a flag)
     * - Using doubly-linked list could waste memory but is easier to 
     *   implement than arrays.
     */

  public:

    AABB * owner;
    /** Value used to sort EndPoint list */
    int value;

    /** Flag to indicate if this EndPoint is minimum of a AABB or not */
    bool isMin;

    /** Previous EndPoint in the list */
    EndPoint * prev;

    /** Next EndPoint in the list */
    EndPoint * next;

    EndPoint (AABB* o,int v,bool m,EndPoint* p=nullptr,EndPoint* n=nullptr);
    
    /** When and EndPoint is destroyed, it updates prev and next */
    ~EndPoint ();
  };

}

#endif
