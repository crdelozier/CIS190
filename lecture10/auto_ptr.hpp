#include <cassert>
#include <iostream>

template <class T>
class auto_ptr{
  T *_p;

public:
  auto_ptr() : _p(nullptr){}

  auto_ptr(T *p) : _p(p) {
    std::cout << "Constructing " << (void*)_p << "\n";
  }

  ~auto_ptr(){
    if(_p != nullptr){
      std::cout << "Deleting " << (void*)_p << "\n";
      delete _p;
    }
  }

  auto_ptr(auto_ptr<T>& other) : _p(other._p) {
    other._p = nullptr;
  }

  auto_ptr<T>& operator=(auto_ptr<T>& other) {
    auto_ptr<T>(other).swap(*this);
    return *this;
  }

  T& operator*() const {
    assert(_p != nullptr);
    return *_p;
  }

  T* operator->() const {
    return _p;
  }

private:
  void swap(auto_ptr<T>& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
  }
};
