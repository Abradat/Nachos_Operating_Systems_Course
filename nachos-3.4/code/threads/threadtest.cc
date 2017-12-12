// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include <sys/time.h>

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

// Test cases

void ThreadForTest0(int which)
{
    int num;
    long int cnt = 0;

    for(num = 0; num < 5; num++)
    {
        for(long int i =0; i < 1000000000; i++)
            cnt++;

        printf("*** ThreadForTest1 thread %d looped %d times \n ", which, num);
        currentThread -> Yield();
    }
}

void 
ThreadForTest1(int which)
{
    int num;
    long int cnt = 0;

    for(num = 0; num < 5; num++)
    {
        for(long int i =0; i < 1500000000; i++)
            cnt++;

        printf("*** ThreadForTest1 thread %d looped %d times \n ", which, num);
        currentThread -> Yield();
    }
}

void 
ThreadForTest2(int which)
{
    int num; 
    long int cnt = 0;

    for(num = 0; num < 5; num++)
    {
        for(long int i =0; i<2000000000; i++)
            cnt++;

        printf("*** ThreadForTest2 thread %d looped %d times \n ", which, num);
        currentThread -> Yield();
    }
}


void
ThreadForTest3(int which)
{
    int num;
    long int cnt = 0;

    for(num = 0; num < 5; num++)
    {
        for(int long i = 0; i < 2500000000; i++)
            cnt++;

        printf("*** ThreadForTest3 thread %d looped %d times \n ", which, num);
        currentThread -> Yield();

    }
}


void
PriorityQueueTest()
{
    DEBUG('t', "Entering Test for Priority Queue");

    Thread *myThread1 = new Thread("Thread1 Created");
    Thread *myThread2 = new Thread("Thread2 Created");
    Thread *myThread3 = new Thread("Thread3 Created");

    currentThread -> priority = 0;

    myThread1 -> priority = 1;
    myThread2 -> priority = 2;
    myThread3 -> priority = 3;

    struct timeval tv;
    gettimeofday(&tv,NULL);

    unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;
    currentThread->startTime=time_in_micros;

    myThread1 -> Fork(ThreadForTest1, 1);
    myThread2 -> Fork(ThreadForTest2, 2);
    myThread3 -> Fork(ThreadForTest3, 3);

    ThreadForTest0(0);

}
//
//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
        case 1:
	       PriorityQueueTest();
	       break;
        default:
	       printf("No test specified.\n");
	       break;
    }
}

