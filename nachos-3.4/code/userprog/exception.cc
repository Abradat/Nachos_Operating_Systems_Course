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


extern Table * TablePtr;



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

/*
 * ForkedThread -> Forked routine to run the forked thread
 */
void ForkedThread(int funcPtr) {
    currentThread->space->InitRegisters();		// set the initial register values
    currentThread->space->RestoreState();		// load page table register

    machine->WriteRegister(PCReg, funcPtr);
    machine->WriteRegister(NextPCReg, funcPtr+4);

    machine->Run();			// jump to the user progam
    ASSERT(FALSE);			// machine->Run never returns;
    // the address space exits
    // by doing the syscall "exit"
}


void forker(void (*func)()) {
    int funcPtr = (int) (func);
    if (!currentThread->space->allocateThreadSpace()) {//when we dont have space for allocating
        return;
    }
    currentThread->SaveUserState();//save Registers
    currentThread->RestoreUserState();//restore register and address of table to

    AddrSpace *space = currentThread->space;
    Thread *forkedThread = new Thread("Forked Thread", 1);
    forkedThread->space = space;//space of forkedThread = allocated space

    TablePtr->Alloc((void *)(forkedThread));
    forkedThread->Fork(ForkedThread, funcPtr);





}

void
ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2);

    if (which == SyscallException) {

        if (type == SC_Halt) {
            DEBUG('a', "Shutdown, initiated by user program.\n");
            interrupt->Halt();


        } else if (type == SC_Fork) {
            DEBUG('a', "Called Fork, initiated by user program");

            void (*a)() = (void (*)()) machine->ReadRegister(4);

            forker(a);

        } else if (type == SC_Exit) {
            printf("exit: %s\n", currentThread->getName());
            currentThread->Finish();
            machine->IncrementPCReg();

        }
    } else {
        printf("Unexpected user mode exception %d %d\n", which, type);
        ASSERT(FALSE);
    }
//
//    if ((which == SyscallException) && (type == SC_Halt)) {
//	DEBUG('a', "Shutdown, initiated by user program.\n");
//   	interrupt->Halt();
//    } else {
//	printf("Unexpected user mode exception %d %d\n", which, type);
//	ASSERT(FALSE);
//    }
}
