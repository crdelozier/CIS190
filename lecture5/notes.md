C++ Classes
-----------

* C++ provides a richer abstraction than structs in classes.  Classes accomplish 
the same goal as structs of grouping data, but they also allow methods to be
grouped with their associated data.

* For example, we might have a "point" struct in a C program that stores the x and 
  y coordinates of a point.  If we want to provide any functionality for this point 
  struct, we would need to define functions that work with a pointer to a point.

``` c
#include <stdlib.h>
#include <stdio.h>

typedef struct point{
    int x;
    int y;
} point;

void init_point(point *p, int x, int y){
    p->x = x;
    p->y = y;
}

void print_point(point *p){
    printf("(%d,%d)\n",p->x,p->y);
}

int point_manhattan_distance(point *p1, point *p2){
    return abs(p1->x - p2->x) + abs(p1->y - p2->y);
}

void add_point(point *p1, point *p2){
    p1->x += p2->x;
    p1->y += p2->y;
}

int equals_point(point *p1, point *p2){
    return p1->x == p2->x && p1->y == p2->y;
}

int main(){
    point p1;
    point p2;
    point *p3 = (point*)malloc(sizeof(point));

    init_point(&p1,1,0);
    init_point(&p2,2,2);
    init_point(&p3,1,0);
    
    print_point(&p1);
    print_point(&p2);

    printf("Distance: %d\n",point_manhattan_distance(&p1,&p2));

    if(equals_point(&p1,&p3)){
        printf("Points are equal!\n");
    }

    add_point(&p1,&p2);

    print_point(&p1);

    free(p3);
    
    return 0;
}
```

* In C++, we can package these methods with the data, rather than having 
  separate functions.  This idiom generally leads to cleaner code and a less
  polluted function namespace.

Classes - Access Modifiers
-----------

* Like Java, C++ allows you to protect data from other pieces of code by 
  giving it an access modifier.  C++ provides 3 levels of access protection:
  public, protected, and private.

* public members are accessible anywhere outside of the class.  These members 
  can get read or written to without a getter or setter method.

* protected members can be accessed within the class or in any child classes.

* private members can only be accessed within the class.  The private modifier 
  is the default access modifier for class members.  For structs, the public 
  modifier is the default access specifier.

```
class Sample{
public:
    int x;

protected:
    int y;

private:
    int z;
};
```

* Note: Class members are only guaranteed to be ordered within memory within a 
  single access specifier.  In the above example, the compiler can place 
  x, y, and z in any order in memory that it chooses to.  In most cases, they 
  will still be placed in a natural order, but this is not guaranteed.  In general,
  your code should not assume any particular ordering for class and struct members.

* Classes can selectively give access to their private and protected members via 
  the "friend" keyword.  Both functions and classes can be friends of a class.  

```
#include <iostream>

class FloatVector{
    float x;
    float y;
    float z;

    friend void printVector(FloatVector);
    friend class FloatVectorFriend;
};

class FloatVectorFriend{
    float x;

public:
    void stealX(FloatVector fv){
        x = fv.x;
    }
};

void printVector(FloatVector fv){
    std::cout << "[" << fv.x << "," << fv.y << "," << fv.z << "]";    
}

int main(){
    FloatVector fv;
    FloatVectorFriend f;

    f.stealX(fv);
    printVector(fv);

    return 0;
}
```

Classes - Constructors and Initializer Lists
-----------

* Class constructors are used to initialize the members of a class.  The constructor
  is called every time that an object is created, either on the stack or on the 
  heap using "new".

* Note: A constructor is NOT called when an object is allocated using "malloc".

* Like other methods and functions in C++, constructors can be overloaded
  to provide different ways of initializing the class.  Usually, you will want 
  to provide a default constructor (with no arguments) that initializes all values
  to zero and at least one more constructor that allows the programmer to properly 
  initialize the fields of the object.

* For simple initialization, constructors can use initializer lists to specify a 
  default value for each member.

```
class IntListNode{
    IntListNode *next;
    int data;

public:
    IntListNode() : next(nullptr), data(0){
    }

    IntListNode(int d) : next(nullptr), data(d){
    }
};
```

* Classes can also define destructors, which release any resources held by 
  the object.  This might include memory allocated using new, open files, and 
  anything else that needs to be cleaned up.

```
class AutoDestroyer{
    int *member;
public:
    AutoDestroyer(){
        member = new int;
    }

    ~AutoDestroyer(){
        delete member;
    }
};
```

* When a class defines a destructor, it generally must also define a copy 
  constructor and an assignment operator.  The compiler will automatically 
  generate a copy constructor and assignment operator for every class.  However,
  as in the above example, the default copy constructor and assignment operators
  might not have the proper behavior.  If we blindly copy "member" to another
  object and try to delete the memory in both destructor calls, we will encounter
  a "double-free" error from the allocator.  Thus, we must define how to handle 
  copies of our object.

```
class AutoDestroyer{
    int *member;
public:
    AutoDestroyer(){
        member = new int;
    }

    ~AutoDestroyer(){
        delete member;
    }

    AutoDestroyer(AutoDestroyer &other){
        member = new int;
        
    }

    AutoDestroyer& operator= (AutoDestroyer &other){
        if (this != &other){
            *member = *other.member;
        }

        return *this;
    }
};

int main(){
    AutoDestroyer ad1;
    AutoDestroyer ad2;

    AutoDestroyer adCopy(ad1);

    ad2 = ad1;

    return 0;
}
```

Operator Overloading
-----------

* To allow for prettier syntax, classes can overload operators.  This means 
  that a class can override standard arithmetic (and others) operators in C++.
 
* In the "point" class example, we had a method that performed an add operation.
  Instead of having a method named "add_point", we could instead define the "+" 
  operator to allow our code to use a more natural syntax.  Rather than calling the 
  "add" method, we can simply use "point1 + point2".

* A handy guide for the syntax of each overloaded operator can be found here:
  http://en.cppreference.com/w/cpp/language/operators

* Matrix class example

Static members
----------

* Classes can have static members that have only a single copy per class, rather than 
  a copy for each object.  Normal object fields are replicated per object.

* Static member fields must be defined outside of the class.  If there is an intial value
  for the static field, it is given in the definition.

```
class Foo{
public:
  static int x;
};
int Foo::x = 0;
```

* Generally, static member field definitions occur in the source file instead of in 
  the header to ensure that they are not defined multiple times.

* Static member fields can be referred to as an object field (e.g. "obj.x") or with the 
  class name (e.g. "Foo::x").

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

User-Defined Conversions
-----------

* Classes can define their own implicit conversions to other types.  For example, 
  a "key" class for a database might convert to a string so that the program 
  can print it.

```
class Key{
  std::string key;

public:
  operator std::string() const {
    return key;
  }
};
```

* Conversions can also be marked as "explicit" if you want to ensure that 
  they are not used implicitly.

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