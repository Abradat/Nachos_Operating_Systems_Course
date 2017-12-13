#ifndef MULTILEVELQUEUE_H_
#define MULTILEVELQUEUE_H_


#include "copyright.h"
#include "list.h"
#include "thread.h"
#include "scheduler.h"
#include "struct.h"
#include "system.h"
#include <sys/time.h>

class multilev:Scheduler{
  public :
    multilev(); //Initialize the multilev
    ~multilev(): //throw away multilev

    Thread* FindNextToRun();
    void ReadyToRun(Thread *threadptr);
    void Run(Thread *threadptr);

  private:
    PriorityQueueScheduler *multi_priority;
    sjf *multi_sjf;
    bool is_sjf_turn;

};


#endif /* MULTILEVELQUEUE_H_ */
