// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"

#define UserStackSize		1024 	// increase this as necessary!

class BitMap;
class Lock;

class MemoryManager {
public:

    /* Create a manager to track the allocation of numPages of physical memory.
     You will create one by calling the constructor with NumPhysPages as
     the parameter.  All physical pages start as free, unallocated pages. */
    MemoryManager(int numPages);

    ~MemoryManager();

    /* Allocate a free page, returning its physical page number or -1
     if there are no free pages available. */
    int AllocPage();

    /* Free the physical page and make it available for future allocation. */
    void FreePage(int physPageNum);

    /* True if the physical page is allocated, false otherwise. */
    bool PageIsAllocated(int physPageNum);

private:
    Lock * lock;     // For synchronization
    BitMap * pages;  // keep track of which pages are available
};

class AddrSpace {
  public:
    AddrSpace(OpenFile *executable);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code

    void SaveState();			// Save/restore address space-specific
    // for now!
    int allocateThreadSpace();

    void RestoreState();		// info on a context switch
private:
    TranslationEntry *pageTable;	// Assume linear page table translation
    unsigned int numPages;		// Number of pages in the virtual

					// address space

};

#endif // ADDRSPACE_H
