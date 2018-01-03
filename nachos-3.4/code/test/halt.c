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
int lastForkedSpaceId;
void fork1()
{
	int cnt;
	for(cnt = 0; cnt < 1; cnt++)
	{
	}
//	Exit(0);
}

void fork2(){
    int i;
    for(i = 0; i < 1; i++){

    }
    return;
   // Exit(100);
}

void fork3(){
    int i;
    for(i = 0; i <1; i++){

    }
}

main(){
	Fork(fork1);
    Join(lastForkedSpaceId);
    Fork(fork2);
    Join(lastForkedSpaceId);
    Fork(fork3);
    Join(lastForkedSpaceId);
    Fork(fork1);
    Join(lastForkedSpaceId);
    Fork(fork1);
    Join(lastForkedSpaceId);
    Fork(fork3);
    Join(lastForkedSpaceId);

}
