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

#include "forkstruct.h"

#include <unistd.h>
#include <sys/time.h>
#include "ForkListElement.h"

//This function gets the timestamp for the unique space id
unsigned long int time_getter(){
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned long int miltime =((long)now.tv_sec*1000) + ((int)now.tv_usec/1000);
    return miltime;
}


//This Function does 3 things
// First stores the current pc register value to the previous pc register
// Second stores the next pc register value to the current pc register
// Third, stores the next pc register value + 4 to the next pc register value
void nextPc(){
    machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
    machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
    machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg) + 4);
}

// This function gives function ptr as a int and stores it in the pc register
// Then changes the next pc register value and run the machine for running userprogram
void runFunction(int functionPtr){
    machine->WriteRegister(PCReg, functionPtr);
    machine->WriteRegister(NextPCReg, functionPtr + 4);
    machine->Run();

}

// This function is fork system call implementation.
// This function creates a new kernel thread (process) named "Forked Thread"
// then sets address space of new thread to the current thread's (parent) addr space
// At the end, forks new thread and returns unique space id for that thread
int ForkI(void (*func))
{
    nextPc(); // shift pc registers values to next level

//    if(joinElement != NULL){
//        DEBUG('a', "Same Thread\n");
//        return lastForkedSpaceId;
//    }
    printf("func: %d\n", (int) func);
    DEBUG('t', "fork started\n");
    Thread *newThread = new Thread("Forked thread"); // creating new thread
    newThread -> space = currentThread -> space; // setting the addr space of the new thread to the current thread's (parent) addr space
    lastForkedSpaceId = time_getter(); // gets the time stamp as the unique id

//    ForkListElement *joinElement = (ForkListElement *)forksList->find(lastForkedSpaceId, currentThread);
    //
    //Forks list is a list (!!!) that stores Fork list Elements of each forked thread
    // Adds new thread with it's information to the fork list
    forksList->Append(new ForkListElement(lastForkedSpaceId, currentThread, newThread));

    newThread -> Fork(runFunction, (int)func); // Forks
    return lastForkedSpaceId; // returns the unique space id
}


// This function finds the fork list element by the given space id and current thread as the parent thread
// Then if the find result is NULL will return -1, Otherwise yields current thread and send it to the end of the schedulers list
// At the end returns EXIT value
int JoinI(int  id)
{
    DEBUG('a', "Join started\n");
    ForkListElement *joinElement = (ForkListElement *)forksList->find(id, currentThread);
    DEBUG('a', "Fork Thread has found\n");
    if(joinElement == NULL) return -1;
    DEBUG('a', "join id: %d\n", id);
    DEBUG('a', "join founded thread space id: %d\n", joinElement->space);
    if (joinElement->parent == currentThread){
        DEBUG('a', "Join Yield\n");
        currentThread->Yield();
    }
    DEBUG('a', "Join finished\n");
    DEBUG('a', "Next pc\n");
    nextPc();
    return machine->ReadRegister(4);

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

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    }

    // Handles the fork system call by calling ForkI function implemented above
    // returns and stores the return value of the forked thread in the second register
	else if((which == SyscallException) && (type == SC_Fork)){
	    DEBUG('a', "Shutdown, Fork.\n");
        machine->WriteRegister(2, ForkI((void (*))(machine->ReadRegister(4))));
    }

    // Handles the join system call by calling JoinI function implemented above

    else if((which == SyscallException) && (type == SC_Join)){
        DEBUG('a', "Shutdown, Join.\n");
	    JoinI(lastForkedSpaceId);
    }
    else if((which == SyscallException) && (type == SC_Exit)){
        interrupt->Halt();
    }

    // Implemented Yield system call
    else if((which == SyscallException) && (type == SC_Yield)){
        nextPc();
        currentThread->Yield();
    }
    else {
	    printf("Unexpected user mode exception %d %d\n", which, type);
	    ASSERT(FALSE);
    }
}


