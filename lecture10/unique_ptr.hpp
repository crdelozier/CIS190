#include <cassert>
#include <iostream>

template <class T>
class unique_ptr{
  T *_p;

public:
  unique_ptr() : _p(nullptr){}

  unique_ptr(T *p) : _p(p) {
    std::cout << "Constructing " << (void*)_p << "\n";
  }

  ~unique_ptr(){
    if(_p != nullptr){
      std::cout << "Deleting " << (void*)_p << "\n";
      delete _p;
    }
  }

  unique_ptr(unique_ptr<T>&& other) : _p(other._p) {
    other._p = nullptr;
  }

  unique_ptr<T>& operator=(unique_ptr<T>&& other) {
    unique_ptr<T>(std::forward(other)).swap(std::move(*this));
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
  unique_ptr(unique_ptr<T>& other) = delete;
  unique_ptr<T>& operator=(unique_ptr<T>& other) = delete;
  
  // How can we prevent users from calling the copy constructor and assignment
  // operator with an lvalue?

  void swap(unique_ptr<T>&& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
  }
};
