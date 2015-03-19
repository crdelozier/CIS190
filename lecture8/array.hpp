#pragma once

#include <iterator>

#include <cstring>
#include <cmath>

#include <iostream>

namespace cis{

template <class T> class array_iterator;

template <class T>
class array{
  T *data;
  unsigned int size;

public:
  array() : data(nullptr) {}

  array(unsigned int _size) : data(nullptr), size(_size){
    data = new T[size];
  }

  void copyFrom(array<T> &other){
    assert(size < other.size);
    std::cout << "Using copyFrom<T>\n";
    for(int c = 0; c < other.size; c++){
      data[c] = other.data[c];
    }
  }

  ~array(){
    if(data != nullptr){
      delete [] data;
    }
  }

  T& operator[] (unsigned int index){
    assert(index < size);
    return data[index];
  }

  array_iterator<T> begin(){
    return array_iterator<T>(this,0);
  }

  array_iterator<T> end(){
    return array_iterator<T>(this,size);
  }
};

template <class T>
class array_iterator{
  array<T> *_array;
  unsigned int _index;

public:
  typedef T value_type;
  typedef int difference_type;
  //typedef forward_iterator_tag iterator_category;
  typedef T* pointer;
  typedef T& reference;

  array_iterator(array<T> *arr, unsigned int index) : 
    _array(arr), _index(index){

  }

  array_iterator<T>& operator++() {
    _index++;
    return *this;
  }

  reference operator*() const{
    return (*_array)[_index];
  }

  template <class U> 
  friend bool operator==(const array_iterator<U>&, 
                  const array_iterator<U>&);
  template <class U>
  friend bool operator!=(const array_iterator<U>&, 
                  const array_iterator<U>&);
};
  
template <class T>
bool operator==(const array_iterator<T>& lhs, 
                const array_iterator<T>& rhs){
  return lhs._index == rhs._index;
}

template <class T>
bool operator!=(const array_iterator<T>& lhs, 
                const array_iterator<T>& rhs){
  return !(lhs == rhs);
}

}
