#include <cassert>
#include <iostream>

template <class T>
class intrusive_ptr{
  T *_p;

public:
  intrusive_ptr() : _p(nullptr) {}

  intrusive_ptr(T *p) : _p(p) {
    std::cout << "Constructing " << (void*)_p << "\n";
  }

  ~intrusive_ptr(){
    if(_p != nullptr){
      if(_p->decrement() == 0){
        std::cout << "Deleting " << (void*)_p << "\n";
        delete _p;
      }
    }
  }

  intrusive_ptr(intrusive_ptr<T>& other) : _p(other._p) {
    if(_p != nullptr){
      _p->increment();
    }
  }

  intrusive_ptr(intrusive_ptr<T>&& other) : _p(other._p) {
    if(_p != nullptr){
      _p->increment();
    }
  }

  intrusive_ptr<T>& operator=(intrusive_ptr<T>& other) {
    intrusive_ptr<T>(other).swap(*this);
    return *this;
  }

  intrusive_ptr<T>& operator=(intrusive_ptr<T>&& other) {
    intrusive_ptr<T>(std::forward(other)).swap(std::move(*this));
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
  void swap(intrusive_ptr<T>& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
  }

  void swap(intrusive_ptr<T>&& other){
    T *tmp = _p;
    _p = other._p;
    other._p = tmp;
  }
};
