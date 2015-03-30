Variadic Templates
-----------

* C and C++ both provide support for functions with variable numbers and types 
  of arguments in the form of "varargs."  Unfortunately, "varargs" are quite
  unsafe to use because they are untyped.

* Functions like "printf" use varargs to allow a variable number and type of 
  arguments.  However, printf and similar functions cannot check to make sure
  that the arguments given to the function are actually the arguments expected.

* Variadic templates provide a type-safe mechanism for having functions and 
  classes with a variable number and type of arguments.

* With variadic templates, we can actually define a type-safe version of 
  printf!

```
void printf(const char *s){
  while (*s) {
    if (*s == '%') {
      throw std::runtime_error("invalid format string: missing arguments");
    }
    std::cout << *s++;
  }
}

template<typename T, typename... Args>
void typesafe_printf(const char *s, T value, Args... args){
  while (*s) {
    if (*s == '%') {
      std::cout << value;
      s += 2;
      typesafe_printf(s, args...);
      return;
    }
    std::cout << *s++;
  }
}
```

* We can also define templated classes with a variable number of 
  parameters.  This is useful in cases like defining a tuple class
  that stores variable types and numbers of data.  For now, we won't
  be covering variadic templated classes because their implementation 
  involves more advanced template metaprogramming concepts than we've 
  covered.

RAII
-----------

* C++ code often follows the concept Resource Acquisition is Initialization
  (RAII).  This means that resources are acquired during the initialization 
  of an object and then released during the destructor.

* For example, when we allocate memory on the heap that will go out of 
  scope at the end of a function (e.g. a dynamically sized array that 
  doesn't escape the function), we want that memory to be deleted (released)
  at the end of the function.

* C++ provides a few mechanisms that use RAII semantics to ease the burden 
  of releasing resources on the programmer.  Below, we will discuss smart
  pointers used in C++ code that give RAII semantics for memory allocations.

Smart Pointers
-----------

* C++11 (and C++14) provide a few new constructs for managing heap-allocated
  memory safely.

* "Smart Pointers" are wrapper around standard C++ pointers that provide 
  additional functionality.  In most cases, this additional functionality 
  aims to prevent memory safety errors that are more likely with standard
  C++ pointers.

* The most common use for smart pointers in C++ is to automate the process
  of deleting memory when the program is finished with it.

* "auto_ptr" and it's newer C++11 version "unique_ptr" call delete on the stored
  pointer on destruction.  Both of these smart pointers assume that only one
  copy of the pointer should exist at any time.  The internal pointer is passed
  from one copy of the smart pointer to the next so that it is only destructed
  (and deleted) once.

* "shared_ptr" performs reference counting to allow multiple copies of the internal
  pointer in the program and guarantees that destruction only happens when the 
  last shared_ptr falls out of scope.

