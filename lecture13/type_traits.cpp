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
