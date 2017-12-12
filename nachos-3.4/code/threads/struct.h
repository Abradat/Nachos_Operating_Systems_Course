#include "thread.h"

class save_time{
	Thread *threadptr;
	int duration;
public:
	save_time();

	void setthreadptr(Thread *thread);
	Thread* getthreadptr();

	void setduration(int newduration);
	int getduration();


};
