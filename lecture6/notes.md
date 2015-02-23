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

Namespaces
-----------

* Namespaces further allow you to "hide" classes and functions from other
  parts of the code.

* The "namespace" directive declares a new namespace.

```
namespace my_namespace{

class Foo{
  ...
};

}
```

* To access the above class "Foo", you must use the fully qualified name
  "my_namespace::Foo".

* Instead of always using the namespace prefix, you can use the "using" 
  directive to specify that any names in that file might be prefixed
  with a namespace.  For example, "using my_namespace;" would allow 
  us to access "Foo" directly.

* In general, "using" declarations should never be included in a header
  file because this will cause the "using" directive to leak to all 
  source and header files that include that header.  Instead, you should 
  scope using directives to the most shallow scope as possible (most 
  likely in the source file).

* Namespaces are generally useful for ensuring that your classes do not 
  collide with other classes of the same name.  For example, a numeric library
  might implement a "vector" that refers to an x, y, and z coordinate, whereas
  a data structure library might implement a "vector" that stores an array of 
  arbitrary size.  Without namespaces, we would have to distinguish the names
  of these classes in some way.  With namespaces, we can simply prefix them
  with "numeric::vector" and "std::vector".

C++ Standard Library Classes
-----------

* The C++ STL (standard library) contains many useful classes for C++ 
  programmers to use.  These classes are all included in the "std" 
  namespace.

iostream
-----------

* The iostream header contains classes for input and output in C++.  We've been 
  using std::cout to output text and formatted data to the console.  The iostream
  header also provides std::cerr for error output and std::cin for input from the 
  console.  cout, cin, and cerr are all instances of "streams" in the C++ standard
  library.  Streams are more generally applicable to input and output in C++.

* "std::istream" is the base class for all input streams in C++.  It defines "operator>>"
  for input and methods such as "read" and "get" for reading from the input stream.

* "std::ostream" is teh base class for all output streams in C++.  It defines "operator<<"
  for output and methods such as "write" and "put" for writing to the output stream.

* istream and ostream are generally used to allow a programmer to define a method 
  that can input or output to either a file or the consolve.  In the example below, 
  we can define a method that prints "Hello World!" to the console and a text
  file using the same code.

```
#include <fstream>
#include <ostream>

void print(std::ostream &out){
  out << "Hello World!\n";
}

int main(){
  std::fstream file("output.txt", std::ios_base::out);

  print(file);
  print(std::cout);

  file.close();

  return 0;
}
```

* In this example, we use "std::fstream" to open a file for writing.  fstream operates
  similarly to file operations in C using "FILE *".  The constructor for fstream takes  
  a file name.  fstream inherits from iostream, which in turn inherits from istream and 
  ostream.  Thus, fstream can perform both input and output on a file.  You can also use
  "ifstream" for input only files and "ofstream" for output only files.

* As with most file classes in programming languages, you need to make sure that you close
  any files that you open.

* The sstream header includes the "stringstream" class, which can be used to generated formatted
  C++ strings.  We will discuss this class more later on.

* The iomanip header contains a few utility functions for dealing with input and output 
  streams in C++.  For example, the "setfill" and "setw" functions can be used to 
  generate output of equal length with a filled in character.

```
#include <iostream>
#include <iomanip>

int main(){
  std::cout << std::setfill('0') << std::setw (5);
  std::cout << 1 << ".tmp" << std::endl;
  std::cout << 2 << ".tmp" << std::endl;
  return 0;
}
```

std::string
-----------

* The "std::string" class in C++ provides a wrapper around C-style strings.  Beneath the covers,
  "std::string" is simply a char* coupled with an integer length field.  However, "std::string" 
  is generally safer to use than C-style strings because it carries its length with it.

* "std::string" is a mutable type.  This means that operations on the string will change the underlying
  data structure instead of making a new copy.  This is reflected in the interface of the "std::string"
  class in that it always returns a reference to a string instead of a copy of the string.
  On the other hand, Java Strings are mutable and always
  generate a new copy of the String.

* The string class contains multiple utility methods.

```
string& operator=(const string& str);

int size();

char& operator[] (int position);
char& at(int position);

string& operator+= (const string &str);
string& append (const string &str);

int compare (const string& str) const;

string& insert (size_t pos, const string& str);

string& replace(size_t pos, size_t len, const string& str);
string& replace(iterator i1, iterator i2, const string& str);

string substr(size_t pos = 0, size_t len = npos);

size_t find (const string& str, size_t pos = 0) const;

iterator begin();
iterator end();
```