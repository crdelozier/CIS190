#include <thread>
#include <mutex>

#include <iostream>

//std::mutex counter_mutex;
int counter = 0;

void increment_counter(){
  for(int c = 0; c < 10000000; c++){
    counter++;
  }
}

int main(){
  std::thread **threads = new std::thread*[4];

  for(int c = 0; c < 4; c++){
    threads[c] = new std::thread(increment_counter);
  }

  for(int c = 0; c < 4; c++){
    threads[c]->join();
  }

  std::cout << "Result: " << counter << "\n";

  return 0;
}
