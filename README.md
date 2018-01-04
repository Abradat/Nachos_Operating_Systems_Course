# Nachos_Operating_Systems_Fall_2017

## Installation

**Don't forget to fork the project because you have to work on this project with your own team in your own repository during this semester**

1) `sudo apt-get install build-essential git csh lpr libc6-dev-i386 gcc-multilib g++-multilib` </br>
2) `git clone https://github.com/sarsanaee/Nachos_Operating_Systems_Course.git` </br>
3) `cd Nachos_Operating_Systems_Course` </br>
4) Please extract source files from Necessary Package directory `tar -xf cse120su10-nachos.tgz -C ../`</br> 
5) Please extract source files from Necessary Package directory `tar -xf mips-x86.linux-xgcc.tgz -C ../` </br>
6) `cd ../nachos-3.4` </br>
7) add the address of mips-x86.linux-xgcc directory to `prepfile.bash` in `nachos-3.4/code/prepfile.bash` don't forget to append a `/` at the end of the path</br>
8) Look around the directories, README files and so on. </br>
9) Go to the code directory `cd code` </br>
10) You already know what is the `make` command so try it :) but do not expect everything goes well :)) </br>

##### If you do not want to follow previous instructions, you can refer to [this](http://homes.cs.washington.edu/~tom/nachos/), however, there are a lot of useful and interesting documents you probably want to read.

## Here is the visual installation :)

[![asciicast](https://asciinema.org/a/b6pc2zok0gagrmyp1e0oi67e2.png)](https://asciinema.org/a/b6pc2zok0gagrmyp1e0oi67e2)

##Project number 2 on branch shayan##

**Fork System Call**
we implemented Fork system call, this system call is defined in /userprog/syscall.h and we implemented it in the /userprog/exception.cc
we changed the return value of the default fork systemcall from void ptr to int to assign a unique value or space id to the new fork threads to handle it later for the join system call

**Join System Call**
we implemented Join system call, this system call is defined in /userprog/syscall.h and we implemented it in the /userprog/exception.cc
this system call yields the thread if it is parent of the our wanted thread.

**New Data Structures**
we implemented some new data structures for running fork and join system calls 
1) ForkListElement -> This class is implemented in the /userprog directory to store new threads information to use it later in the join system call
2) forkList global Variable -> this is nachos default list for saving the list elements

**Schedulers**
you can see the sjf, priority queue and multi level queue schedulers in the test2 branch
