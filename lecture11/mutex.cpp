#include <thread>
#include <mutex>

#include <iostream>

std::mutex counter_mutex_1;
std::mutex counter_mutex_2;
int counter1 = 0;
int counter2 = 0;

void increment_counter(int tid){
  for(int c = 0; c < 10000000; c++){
    if(tid == 0){
      counter_mutex_1.lock();
      counter1++;
      counter_mutex_2.lock();
      counter2++;
      counter_mutex_2.unlock();
      counter_mutex_1.unlock();
    }else{
      counter_mutex_2.lock();
      counter2++;
      counter_mutex_1.lock();
      counter1++;
      counter_mutex_1.unlock();
      counter_mutex_2.unlock();
    }
  }
}

int main(){
  std::thread **threads = new std::thread*[4];

  for(int c = 0; c < 4; c++){
    threads[c] = new std::thread(increment_counter,c);
  }

  for(int c = 0; c < 4; c++){
    threads[c]->join();
  }

  std::cout << "Result: " << counter1 << "\n";

  return 0;
}
