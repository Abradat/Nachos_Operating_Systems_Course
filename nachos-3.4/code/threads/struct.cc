#include "struct.h"
int save_time :: getduration(){
	return duration;

}
Thread* save_time ::getthreadptr(){
	return threadptr;
}
void save_time ::setduration(int  newduration){
	duration = newduration;

}
void save_time ::setthreadptr(Thread *thread){
	threadptr = thread;
}

save_time::save_time() {
	
}