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

Virtual Construction and Destruction
-----------

* Virtual methods allow dynamic overloading of methods on objects that inherit from 
  a base class.

* Normally, methods and functions are bound to calls at compile time.  The compiler 
  does this by examining the types of the arguments and object that the method is 
  being called on.

* Virtual methods are called at runtime by examining the type of the underlying memory
  that holds the object.  A "vptr", or virtual table pointer, stores the address 
  of a table in memory that holds the addresses of all of the virtual methods 
  for a class.  Using this "vptr", the runtime system can call the correct version 
  of a virtual method on an object, depending on the object's type.

* This "vptr" is also used by "dynamic_cast" to check that the type of the object
  matches the expected type.

* When a class inherits from another class, it also inherits the base class member 
  variables.  When we construct an object of the derived class, we must also construct 
  the base class to ensure that all of the base class member variables are initialized
  properly.

* All classes have a default constructor.  If a constructor is not explicitly specified in 
  a base class, the default constructor for the base class will be called in the constructor 
  for the derived class.

* Can we access Base class memory in a derived class constructor?

* Since the base class is always constructed before the derived class, it is safe 
  to access base class member variables in the derived class.

* Can we pass base class members to another base class?

* Base classes are constructed in the order in which they are declared.

```
class Derived : public Base1, public Base2{
  ...
};
```

* In the above example, Base1 will be constructed before Base2.  Thus, we need 
  to ensure that we do not use any of Base2's members in the constructor for 
  Base1.  If we need to use something from Base2 in Base1's constructor, we 
  would need to switch the order of declaration.

* Destructors for base classes are called in reverse order of construction.

* Destructors can be virtual.  If you are using a pointer to a base class to 
  manage a pointer to a derived class and cannot (or do not want to) cast to 
  the derived class before deleting the object, you will need to use a virtual 
  destructor to ensure that the correct destructor is called.  Otherwise, memory 
  leaks can occur.

Templates
-----------

* C++ provides templates to allow programmers to write code that is largely independent 
  of the type of object being used in their code.  For example, templates allow
  programmers to write data structures that can store any type of data without having 
  to resort to void pointers.  This capability allows C++ code (that uses templates) to 
  be better typed than C code.

* To demonstrate the power of templates, let's try to write a linked list that only 
  stores integers.

```
class LinkedListNode{
public:
  int data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode node;
  int d = 5;
  node.data = d;
  int c = node.data;
  return 0;
}
```

* This linked list node will accomplish the task of storing integers in a linked
  list, but it will only store integers.  We can change this structure to store 
  any type of data using void pointers.

```
class LinkedListNode{
public:
  void *data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode node;
  int d = 5;
  node.data = (void*)d;
  int c = (int)node.data;
  return 0;
}
```

* This structure is more flexible because it can store any type of data in the 
  void pointer, but it requires unchecked type-casts that may cause type-safety 
  errors if used incorrectly.

```
template <class T>
class LinkedListNode{
public:
  T data;
  LinkedListNode *next;
};

int main(){
  LinkedListNode<int> node;
  int d = 5;
  node.data = d;
  int c = node.data;
  return 0;
}
```

* Templates allow us to both store anything in our linked list data structure
  while also avoiding unchecked type casts.

* Classes can be templated on either types or on integers.  Templates on integers
  allow interesting tricks like template metaprogramming (to be shown later!).
  Integer templates also allow us to template on the values "true" and "false" 
  implicitly (1 and 0).  Thus, we can design classes that are specialized for 
  specific implementations.

* Template specialization allows us to generate specific code for a certain type.