GUI Programming in C++
-----------

* C++ does not provide the ability to create Graphical User
  Interfaces (GUIs) by default.  Instead, a few libraries
  exist that allow users to create GUIs for their applications.

* A few commonly used GUI frameworks are Qt, gtkmm, and wxWidgets.

Qt
-----------

* Qt provides a few different mechanisms for creating your own GUI 
  applications.

* The Qt IDE provides a drag-and-drop editor (Qt Quick Projects) that 
  can be used to create your own IDE.

* Qt also provides a large API of basic GUI widgets and layouts that
  can be combined to create your own GUI applications.

Boost
-----------

* The Boost library provides additional functionality for C++ programs
  that is not provided by the STL.  Boost is structured similarly to 
  the STL in that it contains containers and algorithms.

* Boost also contains other useful libraries, including regex, file-system
  utilities, graphs, and lock-free containers.

* Boost also contains unique support for inspecting types using template 
  metaprogramming.  The type traits library provides functionality 
  for examining and determining the characteristics of types.

Regex
-----------

* The Boost regex library provides functionality for using regular expressions
  in C++ programs.

* Regular expressions allow a programmer to match a string against some 
  pattern and extract matching pieces of the string.

```
#include <string>
#include <boost/regex.hpp>

int main(){
  std::string str("abc17");
  boost::regex expression("(\\w+)(\\d+)");

  std::cout << boost::regex_match(str,expression);

  return 0;
}
```

* The example above demonstrates how to match a string against a regular expression.
  Note that we need to use "\\" to begin a matching sequence in the regular expression
  because C++ (like Java) uses "\" as an identifier for escape codes, such as "\n" 
  for a newline.

* We can also use regular expressions to capture parts of the string.  The next
  example uses the same expression but extracts the numeric portion.

```
#include <string>
#include <boost/regex.hpp>

int main(){
  std::string str("abc17");
  boost::smatch what;
  boost::regex expression("([a-z]+)(\\d+)");

  std::cout << boost::regex_match(str,what,expression) << "\n";

  std::cout << what.size() << "\n";
  std::cout << what[2] << "\n";

  return 0;
}
```

* In this example, we can use the "smatch" (string match) 
  class to capture results from the regular expression match.

* More information on regular expressions can be found here:
  http://www.regexr.com/

Type Traits
-----------

* The Boost type traits library provides functionality for 
  examining types.  As discussed earlier in the course, template
  specialization and partial template specialization allow a 
  programmer to write special code for a function or class for
  specified types.

* Boost's type traits library provides many different templates
  that can be used for template specialization.

```
#include <iostream>
#include <boost/type_traits.hpp>

class Foo{
};

class Bar{
public:
  Bar(){
    std::cout << "In Bar constructor\n";
  }
};

int main(){
  std::cout << boost::is_void<void>::value << "\n"; // True
  std::cout << boost::is_void<Foo>::value << "\n"; // False

  std::cout << boost::is_pointer<Foo>::value << "\n"; // False
  std::cout << boost::is_pointer<Foo*>::value << "\n"; // True

  std::cout << boost::is_unsigned<int>::value << "\n"; // False
  std::cout << boost::is_unsigned<unsigned int>::value << "\n"; // True

  std::cout << boost::has_trivial_constructor<Foo>::value << "\n"; // True
  std::cout << boost::has_trivial_constructor<Bar>::value << "\n"; // False

  return 0;
}
```

* In the above example, we check a few types for the properties "is_void", 
  "is_pointer", "is_unsigned", and "has_trivial_constructor".

* The Boost type traits library contains many other properties of types 
  that can be checked.  The full listing can be found here:
  http://www.boost.org/doc/libs/1_58_0/libs/type_traits/doc/html/index.html

enable_if
-----------

* enable_if provides the ability to choose a template based off of 
  the traits of a type.

* enable_if exploits the C++ compilation rule that Substitution 
  Failure is Not an Error (SFINAE).

```
int negate(int i) { return -i; }

template <class F>
typename F::result_type negate(const F& f) { return -f(); }
```

* SFINAE is useful because we don't want to break existing code
  by adding templates that the compiler may attempt to instantiate.

* Essentially, all the compiler needs is a single possible option 
  for a function call.  Having additional function calls that 
  fail to instantiate is fine as long as some function exists that 
  can be properly instantiated (type-checks).

* enable_if uses SFINAE to direct the compiler to a specific instantiation
  desired by the programmer.

