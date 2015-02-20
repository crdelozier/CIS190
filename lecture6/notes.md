Casting Operators
-----------

* C++ provides casting operators that are safer to use than C's cast operator.  C's 
  cast operator will always allow the user to cast to the specified type.  C++'s
  cast operators are stronger typed at compile time, and one of the cast operators 
  is checked at runtime.

* "dynamic_cast" is the strongest and most well checked of the C++ cast operators.
  It allows the programmer to cast between different types in a class hierarchy.
  dynamic_cast checks at runtime to ensure that the object being cast is of the 
  actual type that the cast specifies.

* "static_cast" allows the same casts as dynamic_cast but does not check at 
  runtime to ensure that the object being cast is actually the correct type.
  static_cast is therefore faster than dynamic_cast, but it is not as safe 
  as dynamic_cast.  static_cast can also perform the usual primitive type conversions
  that the C cast operator performs.

* "reinterpret_cast" allows casts between unrelated types.  This performs similarly 
  to C's cast operator, but it does not allow multiple casts in a single statement. 
  C's cast operator will also perform casts from "const" to "non-const" or in reverse 
  at the same time as reinterpreting the bits.

* "const_cast" allows casts between const and non-const types.

Inheritance and Virtual Methods
-----------

* C++ classes can inherit from a base class, just like a Java class can extend
  from a base class.  However, C++ classes can inherit from more than one base
  class.

* Like member fields and methods, C++ base classes can have an access modifier.
  The access modifier for a base class lowers the visibility of members of the 
  base class to the level specified when those members are accessed through the 
  inheriting class.

```
class Base{
public:
  int x;
};

class Derived : private Base{
};
```

* In "Derived", x is private, but in "Base", x is public.

* Base class constructors are called in the initializer list 
  of the Derived class.  Each base class must be called by 
  name (i.e. not like Java uses "super(...)").

* C++ allows multiple inheritance.  There is no notion of 
  an interface like in Java.  However, C++ base classes can 
  mimic inheritance by not including any data but just including
  methods.

```
class BaseA{
  int x;
public:
  BaseA(int _x) : x(_x){
  }
};

class BaseB{
  int x;
public:
  BaseB(int _x) : x(_x){
  }
};

class Derived : public BaseA, private BaseB{
public:
  Derived(int value) : BaseA(value), BaseB(value){
  }
};
```
* If a name is used in more than one base class, it must 
  be prefixed with the base class name.  In the above example, 
  "BaseA::x" and "BaseB::x" refer to each version of x.

Const
-----------

* Variables and methods in C++ can be marked as const.  For variables, 
  const means that the variable should not be modified.  For methods, 
  const means that the method does not modify the object.

* Functions often mark arguments as const to indicate to the function 
  caller that the arguments to the function will not be modified.

* As a standard convention, pointer arguments to functions are used
  when the value pointed to might be modified, and references are used
  when the value pointed to will not be modified.