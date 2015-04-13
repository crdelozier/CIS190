#include "auto_ptr.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "intrusive_ptr.hpp"

#define pointer_type intrusive_ptr

class PointMem{
  int bits = 001;
};

class Point{
  int _x;
  int _y;
  int *_count;
  
public:
  Point() : _x(0), _y(0) {}

  Point(int x, int y) : _x(x), _y(y) {}

  void increment(){
    _count++;
  }

  int decrement(){
    return --_count;
  }
};

class Bad{
  pointer_type<Point>& _p;

public:
  Bad(pointer_type<Point>& p) : _p(p) {}
};

pointer_type<Point> bar(pointer_type<Point> p2){
  return p2;
}

void f(pointer_type<Point> p2, pointer_type<Point> p3){
  // Why can't we do this assignment with auto_ptr?
  // p3 = bar(p2);
}

int main(){
  // auto_ptr<Point> p1(new Point);
  // Point *p1 = new Point;
  pointer_type<Point> p1(new Point);
  pointer_type<Point> p2(new Point);
  pointer_type<Point> p3(new Point);

  float x = 1.0523523;

  // p1 == nullptr
  pointer_type<Point> p4(p1);
  // p4 == nullptr
  pointer_type<Point> p5 = p4;

  // What is safe to dereference here?
  
  f(p2,p3);

  // What is safe to dereference here?

  Bad bad(p5);
  
  return 0;
}
