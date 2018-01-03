Explanation of Join system call:
What does join do?
Join is a system call that uses for multithreaded applications, it gives us an ability to control our child processes. How?
When we fork a process it will make a child of that process and when we call join it doesn't stop the main process (or thread) f, it gives us this ability to wait till child works finished and then do whatever we want with our multithreading process.
How to implement?
Thread Class:
In order to implement it first we need to change a bit our thread class.
We must enable an ability which we can set our thread joinable or unjoinable when we make it.
We need to implement two key functions in thread to manage join : canJoin( ) and join( ).	
Exception Class:
In this class we must implement the main join system call with the thread that we already made.
In order to manage join system call initially we need a Table to handle our threads.
In this table we keep all of our threads and with its functions we can manage them.
For example we can allocate them get them with an index. For ease of access we implement the Table in exception.cc class.
After complete implementation of Table is turn to implement join in exception.cc, in the function header we give an id and then we make a new thread assigning id to it. Then we check if we can join that thread if so we call join for that thread and then return its join value.






