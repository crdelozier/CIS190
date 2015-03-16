#pragma once

#include <cstring>
#include <cmath>

#include <iostream>

namespace cis{

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
};

template<>
class array<int>{
  int *data;
  unsigned int size;

public:
  array() : data(nullptr) {}

  array(unsigned int _size) : data(nullptr), size(_size){
    data = new int[size];
  }

  ~array(){
    if(data != nullptr){
      delete [] data;
    }
  }

  void copyFrom(array<int> &other){
    assert(other.size <= size);
    std::cout << "Using copyFrom<int>\n";
    memcpy(data,other.data,other.size * sizeof(int));
  }

  int& operator[] (unsigned int index){
    assert(index < size);
    return data[index];
  }
};

}
