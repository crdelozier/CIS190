#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>
#include <iostream>

//std::condition_variable cv;
std::mutex lock;
bool flag = false;

void consumer(){
  lock.lock();
  std::cout << "Doing wait!\n";
  while(!flag){
    lock.unlock();
    lock.lock();
  }
  std::cout << "Done waiting!\n";
  lock.unlock();
}

void producer(){
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::lock_guard<std::mutex> l(lock);
  std::cout << "Doing notify!\n";
  //cv.notify_one();
  flag = true;
}

int main(){
  std::thread t1(producer);
  std::thread t2(consumer);

  t1.join();
  t2.join();

  return 0;
}
