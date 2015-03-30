#include "auto_ptr.hpp"
#include "unique_ptr.hpp"
#include "shared_ptr.hpp"
#include "intrusive_ptr.hpp"

#define pointer_type auto_ptr

class Point{
  int _x;
  int _y;
  
public:
  Point() : _x(0), _y(0) {}

  Point(int x, int y) : _x(x), _y(y) {}
};

class Bad{
  pointer_type<Point>& _p;

public:
  Bad(pointer_type<Point>& p) : _p(p) {}
};

pointer_type<Point> bar(pointer_type<Point> p){
  return p;
}

void f(pointer_type<Point> p1, pointer_type<Point> p2){
  // Why can't we do this assignment with auto_ptr?
  // p2 = bar(p1);
}

int main(){
  pointer_type<Point> p1(new Point);
  pointer_type<Point> p2(new Point);
  pointer_type<Point> p3(new Point);

  pointer_type<Point> p4(p1);
  pointer_type<Point> p5 = p4;

  // What is safe to dereference here?
  
  f(p2,p3);

  // What is safe to dereference here?

  Bad bad(p5);
  
  return 0;
}
