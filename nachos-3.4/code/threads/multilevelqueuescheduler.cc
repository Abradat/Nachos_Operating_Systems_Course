//our method for running multilevel Queue scheduler is to have to different sjf and priority schedulers which are synchronized-
// -by the top multilevelqueuescheduler object
//then we have to choose a strategy in every swiching time to select either sjf or priority lists to get the cpu next time slice
//our strategy in this code is to have one thread from sjf and then one thread from priority and so on to have a half -
//and fare distribute algorithm to use both sjf and priority algorithms equally. other strategies can be Implemented
//Author : Soheil Rastegar
// 13 Dec 2017

#include "multilevelqueuescheduler.h"


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
