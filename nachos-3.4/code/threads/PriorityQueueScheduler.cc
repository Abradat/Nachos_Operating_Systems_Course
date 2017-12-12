/*
 * PriorityQueueScheduler.cc
 *
 *  Created on: Dec 12, 2017
 *      Author: slytanix
 */

#include "PriorityQueueScheduler.h"

PriorityQueueScheduler::PriorityQueueScheduler() {
	priorityQueueList = new List;

}

PriorityQueueScheduler::~PriorityQueueScheduler() {
	delete priorityQueueList;
}

Thread* PriorityQueueScheduler::FindNextToRun() {
	return (Thread*)priorityQueueList -> Remove();
}

void PriorityQueueScheduler::ReadyToRun(Thread* thread) {

	DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
	thread -> setStatus(READY);
	priorityQueueList->SortedInsert((void*) thread,thread->priority);
}

