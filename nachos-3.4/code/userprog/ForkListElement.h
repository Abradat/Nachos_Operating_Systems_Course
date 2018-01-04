#ifndef FORKEDLISTELEMENT
#define FORKEDLISTELEMENT

#include "../threads/thread.h"


// This class is a data entity for storing space id, parent thread ptr and child thread ptr for each system call
// This class implemented because we can not use malloc in the nachos, and first we implemented this in struct
// and we got error by flushing stack at the end of the fucntions
class ForkListElement{
public:
    ForkListElement(int SpaceId, Thread* Parent, Thread* Child);
    int space;
    Thread* parent;
    Thread* child;
};

#endif