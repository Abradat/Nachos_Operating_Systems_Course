#ifndef SJF_H
#define SJF_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"
#include "struct.h"
#include "system.h"
#include <sys/time.h>

//identify a subclass of Scheduler
class sjf : public Scheduler {

public:
    sjf();			// Initialize list of ready threads
    ~sjf();			// De-allocate ready list

    void ReadyToRun(Thread* thread);	// Thread can be dispatched.
    Thread* FindNextToRun();		// Dequeue first thread on the ready
					// list, if any, and return thread.
    void Run(Thread* nextThread);	// Cause nextThread to start running
    void Print();			// Print contents of ready list

  private:

    List *readyList;
    //Livethread for all threads that in status of blocked or ready(not terminated)
    List *livethread;

};


#endif
