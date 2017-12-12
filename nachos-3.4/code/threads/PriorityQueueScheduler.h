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
	virtual ~PriorityQueueScheduler();

	Thread* FindNextToRun();
	void ReadyToRun(Thread* thread);

private:
	List *priorityQueueList;

};

#endif /* THREADS_PRIORITYQUEUESCHEDULER_H_ */
