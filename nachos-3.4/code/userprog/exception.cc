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
	else if((which == SyscallException) && (type == SC_Fork)){
	DEBUG('a', "Shutdown, Fork.\n");
	        interrupt->Halt();
}
else if((which == SyscallException) && (type == SC_Fork)){
		DEBUG('a', "Shutdown, Join.\n");
	        interrupt->Halt();
}
else if((which == SyscallException) && (type == SC_Exit)){
        interrupt->Halt();
    }
else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}


unsigned long int time_getter(){
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned long int miltime =((long)now.tv_sec*1000) + ((int)now.tv_usec/1000);
    return miltime;
}

void Fork(void (*func)())
{
    printf("Fork Fork Fork\n");
	Thread *newThread = new Thread("Forkeding thread");
//    DEBUG('t', "fork started");
    newThread -> space = currentThread -> space;
	newThread -> Fork(reinterpret_cast<VoidFunctionPtr>(func), 3);

	lastForkedSpaceId = time_getter();
	ForkStruct myForkStruct = {.parentThread = currentThread, .childThread = newThread, .mySpaceId = lastForkedSpaceId};
	myList -> Append(&myForkStruct);

}

int Join(SpaceId id)
{
	 ForkStruct *forkedThread = (ForkStruct *)myList -> find(id, currentThread);
	 while(forkedThread -> childThread->getStatus() != BLOCKED )
	 {
         currentThread -> Yield();
	 }
	 DEBUG('t', "Join valud", machine->ReadRegister(4));
	 return machine->ReadRegister(4);

}

