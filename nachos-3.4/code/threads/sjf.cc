#include "sjf.h"

sjf::sjf(){
  mylist = new List;
}

sjf::~sjf(){
  delete mylist;
}

void
sjf::ReadyToRun (Thread *thread)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    ListElement* foundedElement = livethread->find(thread);
    if(foundedElement != NULL){ // thread has scheduled before and we add save_time object to the readyList with duration priority
        readyList ->SortedInsert(foundedElement->item, ((save_time*)foundedElement->item)->getduration());

    }
    else{
        readyList->Append(thread);      // this thread has not scheduled yet, so we append it to the readyList for scheduling.
    }
    }

void sjf::Run(Thread *nextThread) {
    Scheduler::Run(nextThread);
    //for getting time
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;


    currentThread->setStartTime(ms);
    ListElement* foundedElement = livethread->find(nextThread);
    if(foundedElement != NULL){
        save_time* temp = ((save_time *)foundedElement->item);
        temp->setduration(ms - temp->getthreadptr()->getStartTime());
    } else{
        save_time* new_time = new save_time();

        save_time * temp = ((save_time *)foundedElement->item);

        new_time->setthreadptr(oldThread);
        new_time->setduration(ms - temp->getthreadptr()->getStartTime());
        livethread->Append(new_time);
    }

}
void sjf::delelement(Thread *threadptr){
	readyList->removeElement(threadptr);
}
