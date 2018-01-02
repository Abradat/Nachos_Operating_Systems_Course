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
// For now, this only handles the Halt() system call.
// Everything else core dumps.
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
#include "../threads/thread.h"
#include "../machine/sysdep.h"

extern Table * TablePtr;


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.



//----------------------------------------------------------------------

//----------------------------------------------------------------------
//implementing Table class methods.
// Table Cons , Alloc , Get

//----------------------------------------------------------------------

/*
  Table's constructor.
*/

Table::Table(int size)
{

    lock = new Lock("lock for the table in syscall"); // this is the variable that locks the table
                                                      // when systemcall arises.

    tableSize = size; // this will assign the table size with the size that we give the function.

    tableptr = new void*[size]; // this will initialize the table pointer with the given size of table.

    for(int i = 0; i < size; i++) {
        tableptr[i] = NULL;
    }


}

/*
  Alloc : this will allocate tableptr in the table for later usage.

*/

int
Table::Alloc(void * object){

    lock->Acquire(); // because we want to change the table.

    for(int i = 0; i < tableSize; i++) {
        if(tableptr[i] == NULL) {
            tableptr[i] = object; // assign an object in the table if the table cell is null or initialized.
            lock->Release(); // after making changes on the table the lock will be released.
            return i; // return changed index of the table.
        }
    }

    lock->Release();

    return -1;
}

/*
 *Get : it takes an index of the table and return a pointer that refers to that index of the table.
 */
void *
Table:: Get(int index) {
    lock->Acquire(); // again because we want to work with the table we arise the lock till others can't work
                     // while we are changing it.

    if(index >= tableSize || index < 0 ) { // here we check the correctness of the index.
        lock->Release();
        return NULL;
    }

    void * toReturn = tableptr[index]; // if the index is correct we return the correspond cell of the table.

    lock->Release(); // after we finished our work with the table we release the lock.

    return toReturn; // return the correspond cell of the table.
}


void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    } else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}

int Join2(SpaceId id) {

    Thread * joinThread = (Thread *) TablePtr->Get(id-1);

    if(joinThread == NULL) {
        fprintf(stderr, "Incorrect ID, cannot join\n");
        return -65535;
    }

    if(!joinThread->canJoin()) {
        fprintf(stderr, "Thread unjoinable, cannot join\n");
        return -65535;
    }

    joinThread->join();

    int retVal = joinThread->getJoinValue();

    return retVal;
}
