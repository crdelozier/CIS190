#include <cassert>
#include <iostream>

template <class T>
class shared_ptr{
  T *_p;
  int *_count;

public:
  shared_ptr() : _p(nullptr), _count(nullptr) {}

  shared_ptr(T *p) : _p(p), _count(new int) {
    *_count = 1;
    std::cout << "Constructing " << (void*)_p << "\n";
  }

  ~shared_ptr(){
    if(_p != nullptr){
      (*_count)--;
      if(*_count == 0){
        std::cout << "Deleting " << (void*)_p << "\n";
        delete _p;
        delete _count;
      }
    }
  }

  shared_ptr(shared_ptr<T>& other) : _p(other._p), _count(other._count) {
    if(_p != nullptr){
      (*_count)++;
    }
  }

  shared_ptr(shared_ptr<T>&& other) : _p(other._p), _count(other._count) {
    if(_p != nullptr){
      (*_count)++;
    }
  }

  shared_ptr<T>& operator=(shared_ptr<T>& other) {
    shared_ptr<T>(other).swap(*this);
    return *this;
  }

  shared_ptr<T>& operator=(shared_ptr<T>&& other) {
    shared_ptr<T>(std::forward(other)).swap(std::move(*this));
    return *this;
  }

  T& operator*() const {
    assert(_p != nullptr);
    return *_p;
  }

  T* operator->() const {
    assert(_p != nullptr);
    return _p;
  }

private:
  void swap(shared_ptr<T>& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
    int *tmpcount = _count;
    _count = other._count;
    other._count = tmpcount;
  }

  void swap(shared_ptr<T>&& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
    int *tmpcount = _count;
    _count = other._count;
    other._count = tmpcount;
  }
};
