/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
SpaceId lastForkedSpaceId;
void fork1()
{
	int cnt;
	for(cnt = 1; cnt <= 1000; cnt++)
	{
	}
	Exit(0);
}

void fork2(){
    int i;
    for(i = 0; i < 100; i++){

    }
    Exit(100);
}

main(){
	Fork(fork1);
	Join(lastForkedSpaceId);
    Fork(fork2);
    Join(lastForkedSpaceId);
}
