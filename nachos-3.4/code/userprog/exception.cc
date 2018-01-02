// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "Table.h"
#include "SynchConsole.h"
#include "Pipe.h"

// External variables used
extern Table * TablePtr;
extern Table * storeTable;
extern MemoryManager * memoryManager;

extern Statistics * stats;

extern SynchConsole * synchConsole;

extern CoreMap * coreMap;


// Table Class //

/*
 * Table's constructor
 */
Table::Table(int size){
    lock = new Lock("lock for the table in syscall");
    tableSize = size;
    tableptr = new void*[size];

    for(int i = 0; i < size; i++) {
        tableptr[i] = NULL;
    }
}

/*
 * Alloc - Allocates void pointers to a table for later access
 */
int Table::Alloc(void * object){
    lock->Acquire();

    for(int i = 0; i < tableSize; i++) {
        if(tableptr[i] == NULL) {
            tableptr[i] = object;
            lock->Release();
            return i;
        }
    }

    lock->Release();

    return -1;
}

/*
 * Get - Gets a void pointer at a particular index in the table
 */
void * Table:: Get(int index) {
    lock->Acquire();

    if(index >= tableSize || index < 0 ) {
        lock->Release();
        return NULL;
    }

    void * toReturn = tableptr[index];

    lock->Release();

    return toReturn;
}

/*
 * Release - Removes a void pointer from the table at a particular index
 */
void Table::Release(int index) {
    lock->Acquire();

    if(index >= tableSize || index < 0 ) {
        lock->Release();
        return;
    }

    tableptr[index] = NULL;

    lock->Release();
}