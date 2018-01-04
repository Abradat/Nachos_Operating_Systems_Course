#include "ForkListElement.h"

ForkListElement::ForkListElement(int SpaceId, Thread* Parent, Thread* Child){
    space = SpaceId;
    parent = Parent;
    child = Child;
}