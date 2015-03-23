#include <iostream>

int main(){
  int arr[3] = {1,2,3};
  
  // Old syntax
  for (int c = 0; c < 3; c++){
    std::cout << arr[c] << "\n";
  }
  
  for (auto x : arr){
    std::cout << x << "\n";
  }

  return 0;
}
