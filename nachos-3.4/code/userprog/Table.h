//
//
//

#ifndef NACHOS_OPERATING_SYSTEMS_COURSE_TABLE_H
#define NACHOS_OPERATING_SYSTEMS_COURSE_TABLE_H

#include "synch.h"
#include "../threads/synch.h"

class Table {

public:

    // Create a table to hold at most "size" entries.
    Table(int size);


    // Allocate a table slot for "object" that is a thread that we made.
    int Alloc(void * object);



    //this method gives an index and returns an object from table.
    void * Get(int index);


private:

    Lock * lock;

    void ** tableptr;

    int tableSize;
};


#endif //NACHOS_OPERATING_SYSTEMS_COURSE_TABLE_H
