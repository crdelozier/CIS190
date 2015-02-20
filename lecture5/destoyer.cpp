#include <iostream>

class auto_ptr{
    int *member;

public:
  auto_ptr() : member(){
    member = new int;
    std::cout << "In constructor\n";
  }

  ~auto_ptr(){
    delete member;
    std::cout << "In destructor\n";
  }

  auto_ptr(auto_ptr &other){
    member = new int;
    *member = *(other.member);
    std::cout << "In copy constructor\n";
  }

  auto_ptr& operator= (auto_ptr &other){
    std::cout << "In assignment\n";
    if (this != &other){
      *member = *other.member;
    }  
    return *this;
  }
};

void f(auto_ptr p){
  std::cout << "in f\n";
}

int main(){
    auto_ptr ad1;
    auto_ptr ad2;

    auto_ptr adCopy(ad1);
    ad2 = ad1;

    f(ad1);

    return 0;
}
