#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>
#include <iostream>

std::condition_variable cv;
std::mutex lock;

void producer(){
  std::unique_lock<std::mutex> l(lock);
  std::cout << "Doing wait!\n";
  cv.wait(l);
  std::cout << "Done waiting!\n";
}

void consumer(){
  //std::this_thread::sleep_for(std::chrono::seconds(1));
  std::lock_guard<std::mutex> l(lock);
  std::cout << "Doing notify!\n";
  cv.notify_one();
  std::cout << "Did notify!\n";
}

int main(){
  std::thread t2(consumer);
  std::thread t1(producer);

  t1.join();
  t2.join();

  return 0;
}
