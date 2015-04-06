Parallel Programming in C++11
-----------

* C++11 provides new constructs for writing 
  parallel programs in C++.  Prior to C++11, 
  parallel programming in C++ required the use
  of one of many libraries based on POSIX threading
  support.

* Underneath the covers, the C++11 threading support is
  still based on POSIX threading, but the new C++11 
  support for threading is much more type-safe.

Threads
-----------

* C++11 provides the "thread" class that provides 
  lightweight threading functionality.

* The constructor for the thread class takes a function 
  and the arguments to that function.

* In contrast, the POSIX threading library creates threads
  given a "pthread_t" thread identifier, a function pointer
  to a function that returns a void* and takes a void*, and a 
  void* argument.

```
typedef struct f_args{

} f_args;

void* f (void* arg){
  f_args *args = (f_args*)arg;
  // Stuff
}

int main(){
  pthread_t thread;
  f_args args;
  pthread_create(&thread,NULL,f,(void*)&args);

  pthread_join(&thread, NULL);

  return 0;
}
```

* C++11 provides a much nicer syntax for creating threads.

```
typedef struct f_args{

} f_args;

void f(f_args *args){
  // Stuff
}

int main(){
  f_args args;
  std::thread thread(f,&args);
  
  thread.join();

  return 0;
}
```

Synchronization
-----------

* Threads allow the programmer to perform more than one task at a 
  time.  In many cases, this means that two threads may be updating
  the same variable or structure.  To ensure that this is accomplished
  correctly, synchronization is required to prevent more than one thread 
  from accessing a shared structure at a time.

* Synchronization comes in two forms: atomicity and ordering.  Locks and 
  atomics provide atomicity, and condition variables and barriers provide
  ordering.

* A "mutex" provides "mutual exclusion", meaning that only a single thread
  can enter the code protected by a mutex at a time.

* C++11 provides RAII wrapper classes for use with mutexes.  "lock_guard" provides
  scoped locking of a mutex.  This class unlocks the mutex when it goes 
  out of scope.  "unique_lock" provides similar functionality but is movable 
  (using rvalue references).

* Condition variables provide the ability for a thread to wait for another thread
  to wake it up.  For example, a consumer thread might wait for a producer
  thread to give it some values to compute on.

* Barriers provide the ability to synchronize with a group of threads in lock-step.
  A barrier prevents a thread from continuing to execute until all other threads 
  have reached the same point in their executions.