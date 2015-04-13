#include <atomic>
#include <thread>
#include <iostream>

class barrier{
  std::atomic<int> _count;
  int _total;

public:
  barrier(int total) : _count(0), _total(total) {}

  void wait(){
    _count++;
    while(_count != _total){}
  }
};

void do_wait(barrier *b){
  std::cout << "Before wait!\n";
  b->wait();
  std::cout << "After wait!\n";
}

int main(){
  barrier b(4);
  std::thread **threads = new std::thread*[4];

  for(int c = 0; c < 4; c++){
    threads[c] = new std::thread(do_wait,&b);
  }

  for(int c = 0; c < 4; c++){
    threads[c]->join();
  }

  return 0;
}
