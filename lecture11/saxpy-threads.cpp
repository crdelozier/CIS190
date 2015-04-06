#include <thread>
#include <chrono>

#include <iostream>
#include <cstdlib>

void saxpy(int start, int end, float a, float *x, float *y, int iters) {
  for (int c = 0; c < iters; c++){
    for (int i = start; i < end; ++i){
      y[i] = a*x[i] + y[i];
    }
  }
}

int main(int argc, char **argv){
  using namespace std::chrono;

  if(argc != 3){
    std::cout << "Usage: " << argv[0] << " [number] [iterations]\n";
    exit(1);
  }

  int num = atoi(argv[1]);
  int iters = atoi(argv[2]);
  
  float *x = new float[num];
  float *y = new float[num];

  for(int i = 0; i < num; i++){
    x[i] = (float)(rand() % 10000);
    y[i] = (float)(rand() % 10000);
  }
  
  std::thread **threads = new std::thread*[4];
  
  high_resolution_clock::time_point start = high_resolution_clock::now();

  int first = 0;
  int chunk = num / 4;

  for(int i = 0; i < 3; i++){
    threads[i] = new std::thread(saxpy,first,first + chunk,5,x,y,iters);
    first += chunk;
  }
  threads[3] = new std::thread(saxpy,first,num,5,x,y,iters);

  for(int i = 0; i < 4; i++){
    threads[i]->join();
  }

  high_resolution_clock::time_point stop = high_resolution_clock::now();

  auto time = duration_cast<nanoseconds>(stop-start);
  std::cout << "Saxpy: " << time.count() << " ns\n";

  delete [] x;
  delete [] y;

  return 0;
}
