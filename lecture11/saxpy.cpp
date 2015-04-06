#include <chrono>

#include <iostream>
#include <cstdlib>

void saxpy(int n, float a, float *x, float *y) {
  for (int i = 0; i < n; ++i){
    y[i] = a*x[i] + y[i];
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

  high_resolution_clock::time_point start = high_resolution_clock::now();

  for(int i = 0; i < iters; i++){
    saxpy(num,5,x,y);
  }

  high_resolution_clock::time_point stop = high_resolution_clock::now();

  auto time = duration_cast<nanoseconds>(stop-start);
  std::cout << "Saxpy: " << time.count() << " ns\n";

  delete [] x;
  delete [] y;

  return 0;
}
