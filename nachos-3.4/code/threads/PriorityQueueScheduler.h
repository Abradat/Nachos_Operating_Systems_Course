/*
 * PriorityQueueScheduler.h
 *
 *  Created on: Dec 12, 2017
 *      Author: slytanix
 */

#ifndef THREADS_PRIORITYQUEUESCHEDULER_H_
#define THREADS_PRIORITYQUEUESCHEDULER_H_

#include "scheduler.h"

class PriorityQueueScheduler:public Scheduler {
public:
	PriorityQueueScheduler();
	~PriorityQueueScheduler();

	Thread* FindNextToRun();
	void ReadyToRun(Thread* thread);
	void delelement(Thread *threadptr); //function for deleting a specified thread from sjf list (used in multilevel queue algorithm)
private:
	List *priorityQueueList;

};

#endif /* THREADS_PRIORITYQUEUESCHEDULER_H_ */
