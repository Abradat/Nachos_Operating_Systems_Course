Implement by :AhmadReza Sezavar

Implementing Exit syscall:

(*)What is exit syscall:
    terminates the calling process "immediately". Any open file descriptors
    belonging to the process are closed;
    any children of the process are inherited by process 1, init, and
    the process's parent is sent a SIGCHLD signal

(*)What does Zombie Process mean?

   A zombie process is a process in its terminated state.
   This usually happens in a program that has parent-child functions.
   After a child function has finished execution,
   it sends an exit status to its parent function.
   Until the parent function receives and acknowledges the message,
   the child function remains in a “zombie” state, meaning it has executed but not exited

We started first by writing the Table class in Table.h and implementing it in
exception.cc and used locks and condition variable to synchronize access to
Table. We used the Table to store all the threads that were created to run
either a new process or a forked thread of a process, so that we can access them
later.
