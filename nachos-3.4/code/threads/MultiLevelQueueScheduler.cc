/*
 * MultiLevelQueueScheduler.cc
 *
 *  Created on: Dec 12, 2017
 *      Author: Soheil
 */

#include "MultiLevelQueueScheduler.h"

multilev::multilev(){
    multi_priority = new PriorityQueueScheduler();
    multi_sjf = new sjf();
    is_sjf_turn = FALSE;
}

multilev::~multilev(){
    delete multi_priority;
    delete multi_sjf;

}

Thread *multilev::FindNextToRun(){
    //every time FindNextToRun is called , turn is changing and another method give us it's proposed thread to run
    if(is_sjf_turn){
        Thread *nextthread = multi_sjf->FindNextToRun();
        multi_priority->delelement(nextthread); //notice that when we have to delete the thread from the other object queue otherwise every thread runs twice
        is_sjf_turn = FALSE;
        return nextthread;
    }
    else{
        Thread *nextthread = multi_priority->FindNextToRun();
        multi_sjf->delelement(nextthread);
        is_sjf_turn = TRUE;
        return nextthread;
    }


}

void multilev::ReadyToRun(Thread *threadptr){
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());
    thread -> setStatus(READY);
    multi_sjf->ReadyToRun(threadptr);
    multi_priority->ReadyToRun(threadptr);
}

void multilev::Run(Thread *threadptr){
  if(is_sjf_turn){
    multi_priority->Run(threadptr); //if is_sjf_turn is True it means that previously FindNextToRun methon is called with is_sjf_turn False arguman
  }
  else{
    multi_sjf->Run(threadptr); //same as above
  }
}