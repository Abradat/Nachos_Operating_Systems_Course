/*
 *  * for.c
 *   *
 *    * Simple program to test fork system call.
 *     */

#include "syscall.h"
#include "copyright.h"


void fork3() {
//    Write("I was forked 3\n", 15, ConsoleOutput);
    Exit(2);
}

void fork2() {
//    Write("I was forked 2\n", 15, ConsoleOutput);
    Fork(fork3);
    Exit(3);
}

void fork1() {
//    Write("I was forked 1\n", 15, ConsoleOutput);
//    Write("Yielding\n", 9, ConsoleOutput);
    Yield();
    Exit(100);
//    Write("Back to function, going to exit here\n", 37, ConsoleOutput);
}

int
main()
{

//    DEBUG('a', "Called Yield, initiated by user program");
//    Write("I'm main\n", 9, ConsoleOutput);
    Fork(fork1);
//    Write("Yielding\n", 9, ConsoleOutput);
    Yield();
    Fork(fork2);
//    Write("Back to main, yielding again\n", 29, ConsoleOutput);
    Yield();
    Exit(1);
}
