C++11
-----------

* The ISO C++ Standard defines the standard syntax and semantics
  for the C++ programming language.  In 2011, ISO approved the 
  C++11 standard that updated the language to include a few new
  features.

* Some notable features are constexpr, rvalue references, variadic
  templates, initializer lists, range-based for-loops, and 
  lambda functions.

LValues and RValues
-----------

* In the code we've looked at so far, we've seen lvalues and 
  rvalues, but we haven't talked about what they are and 
  their importance.

* An "lvalue" is a value that can appear on either side of 
  an assignment operation.  These are values that the 
  programmer can explicitly store into.

* At the compiler level, an lvalue is generally something
  that is stored to.

* An "rvalue" is a value that can only appear on the right
  side of an assignment operation.  For example, a constant
  numeric value would be considered an rvalue.

```
int x,y;
x = y; // x and y are both lvalues
5 = x; // Nonsense, 5 is an rvalue and cannot be assigned into
y = 2; // Fine, y is an lvalue and 2 is an rvalue
x + y = 3; // Nonsense, x + y is a temporary result and therefore an rvalue
```

Rvalue References
-----------

* C++11 introduces the concept of rvalue references.  These are different
  than standard references because at compile time, function overloads
  that have an rvalue reference overload will be chosen for rvalue arguments.

* Why are rvalue references useful?  They allow programmers to implement
  "move semantics" in the case that they know a function is being called
  with an rvalue rather than with an lvalue.  To further explain, rvalue
  references allow the programmer to provide a more optimized implementation 
  in the case that the function argument is a temporary value.

* As an example, a vector or array might provide an assignment operator 
  with move semantics that simply steals the pointer to the internal 
  memory used by the vector or array, rather than constructing a 
  copy of the internal memory.

```
array& operator=(array &other){
  delete [] this->_data;
  this->_data = new T[other._size];
  for(int c = 0; c < other._size; c++){
    this->_data[c] = other._data[c];
  }
  this->_size = other._size;
  return *this;
}

array& operator=(array &&other){
  delete [] this->_data;
  this->_data = other._data;
  this->_size = other._size;
  other._data = nullptr;
  other._size = 0;
  return *this;
}
```

* As you can see from the example above, a function that uses move semantics
  can be much more efficient than its non-move counterpart because it can 
  assume that the argument will not be used in the future.  Any function that
  accepts an lvalue must assume that the lvalue argument may still be used
  later in the program.  Thus, the internal storage of the lvalue cannot be
  "stolen" like it can from an rvalue.

* We can also force rvalue reference semantics with the "std::move" function.
  This function transforms an lvalue into an rvalue and allows it to be 
  used with the rvalue reference version of a function or method.  For example, 
  this can be used with a swap function, where we explicitly want to exchange
  the underlying memory between the two lvalues.

```
void swap(T& lhs, T& rhs){
  T tmp(std::move(lhs));
  lhs = std::move(rhs);
  rhs = std::move(tmp);
}
```

* The code in the above example works because tmp will never be used after this 
  function, and lhs and rhs should explicitly swap their internal representations.
  This is more efficient than creating a copy of lhs, copying rhs into lhs, and 
  then copying the copy of lhs into rhs.

* Once an rvalue reference has a name, it will be treated as an lvalue.  Thus, if
  we have an rvalue reference as a function argument, we cannot simply pass that
  rvalue reference into another function or method and expect it to be treated as 
  an rvalue reference again.  To fix this issue, C++11 provides the "std::forward"
  function that takes a refernce and turns it into an rvalue reference.  This allows
  a function to take its rvalue reference arguments and forward them to other 
  functions (such as copy constructors and assignment operators) as rvalue references
  instead of as regular references.  This problem is known as "perfect forwarding".

constexpr
-----------

* The "const" keyword in C++ allows a programmer to specify that some variables are 
  constant.  This const keyword prevents the program from modifying the values of these
  variables.  However, there are some limitations to const.

* Methods can be declared as const, but this does not allow the method to be used as a
  constant expression (e.g. as a size for a static-sized array).  Instead, having a 
  const specifier on a method means that the method will not change the object on 
  which it is implemented.

* C++11 introduces the "constexpr" keyword that allows functions and non-integer
  expressions to be specified as constant.

* The main benefit of this change is that you can specify constexpr functions instead
  of having to use typedef macros.

```
#define SHIFT_N(n) (1 << n)

constexpr int shift_fn(int n){
  return 1 << n;
}
```

* The constexpr version of the code above is much safer to use because it can 
  be type checked by the compiler.  The macro version will work on any type 
  that a shift can be performed on.  Macros often lead to type issues later 
  in compilation where the macro is used.  Therefore, it can be difficult to 
  debug type errors associated with macro expressions.

auto and decltype
-----------

* As we've already seen with iterators, C++11 provides the "auto" keyword for 
  automatically determining the type of a variable.  Variables can be 
  declared as "auto var" instead of "type var", and the compiler will handle 
  the details of what type the variable should be.

```
int x = 5;
auto y = x;
```

* The compiler can determine from the type of expression on the right side of 
  the assignment that "y" should be an int.

* It is sometimes necessary to match the type of a variable that has been declared
  using "auto".

```
int x = 5;
auto y = x;
auto z = f();
// Some code in between
auto result = y + z;
```

* Suppose that we want to ensure that "y" and "z" have the same type.  If we use auto, 
  it might be possible that "f()" returns a double instead of an int, leading to a type
  conversion error later in the program.  If this might be the case, it would be better
  to detect the type error when we declare "z" rather than when we use the variable.  To 
  do this, we can use "decltype" to declare "z".

```
int x = 5;
auto y = x;
decltype(y) z = f();
// Some code in between
auto result = y + z;
```

* This new version of the code ensures that z has the same type as y, even though we 
  don't know exactly what the type of "y" is from its declaration.

For-Loops
-----------

* C++11 provides range-based for loops to replace the traditional declaration, 
  exit condition, increment based for-loop.

```
int arr[3] = {1,2,3};

// Old syntax
for (int c = 0; c < 3; c++){
  std::cout << arr[c] << "\n";
}

for (auto x : arr){
  std::cout << x << "\n";
}
```

* Range-based for loops can be used with any type that provides "begin()" and "end()"
  methods.

* Note: Range-based for loops cannot be used with heap allocated arrays because heap
  allocated arrays do not have a guaranteed size associated with them.

Lambda Functions
-----------

* Many programming languages provide support for "anonymous functions" or "lambda functions."
  These functions are generally defined inline where they will be used and are used for 
  throwaway functions that are not necessary for the rest of the program.  For example, 
  a program might define a "compare" function to sort an array of objects.  If this compare
  function is only used once in the code, it doesn't make sense to define a real function 
  for comparing those objects.

* Lambda functions in C++11 have the following syntax:

```
[capture](parameters) -> return_type { function_body }
```

* As an example, we can define a lambda function that computes the sum of two values:

```
[](int x, int y) -> int { return x + y; }
```

* The "capture" argument specifies what values from outside of the lambda function will 
  be used in the body of the lambda function.  For example, we can capture all of the 
  program's current state for use in the lambda function using "[=]" (by copy) or 
  "[&]" (by reference).  We can also capture specific variables by using "[z]" or 
  "[&z]".

* In general, we want to capture as little of the program state as is necessary to allow
  our lambda functions to be better optimized.

* Lambda functions are commonly used with "for_each", "accumulate", and the other
  functions that take a function argument in the STL algorithm header.

override and final
-----------

* C++11 also adds some additional syntactical constructs for writing classes that use
  virtual methods.

* As you recall, virtual methods can be overridden by derived classes to provide a different
  implementation than the base class.  Two problems can arise when working with virtual methods.
  First, it is possible to accidentally create a new virtual method rather than overriding the 
  old one if the wrong method signature is used.

```
class Base{
public:
  virtual void print(int x);
};

class Derived : public Base{
public:
  virtual void print(float x);
};
```

* In the example above, print(float) actually overrides the print(int) method as a separate
  method overload, rather than a virtual function override.  Luckily, C++11 provides the 
  "override" keyword to ensure that a method actually overrides some base class method.

```
class Base{
public:
  virtual void print(int x);
};

class Derived : public Base{
public:
  virtual void print(int x) override;
};
```

* The override keyword informs the compiler that it should check for a matching method 
  in the base class.  If there is no matching method, the compiler will throw an error.

* Another common error with virtual methods is to override a method in a 
  derived class when the base class wanted the method to be used for all
  derived classes.

* In the example above, it might be the case that "print" should only be implemented
  on the base class.  If the programmer intends for this to be the case, there is 
  no way (prior to C++11) for them to specify this information.

```
class Base{
public:
  virtual void print(int x) final;
};
```

* The "final" keyword allows the Base class writer to specify that no derived classes
  may override the implementation provided in the base class.

* The "final" keyword can be used at any point in the class hierarchy to cut off 
  further virtual method overrides.

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