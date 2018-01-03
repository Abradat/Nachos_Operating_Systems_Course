
#ifndef FORKSTRUCT
#define FORKSTRUCT
#include "../threads/thread.h"

struct ForkStruct
{
	Thread *parentThread;
	Thread *childThread;
	int mySpaceId;

};

#endif
