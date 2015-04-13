#include <vector>
#include <iostream>
#include <algorithm>

template <class Iterator>
void print(Iterator begin, Iterator end){
  for(Iterator it = begin; it != end; it++){
    std::cout << *it << ",";
  }
  std::cout << "\n";
}

int main(){
  std::vector<int> v = {1,2,3};

  print(v.begin(),v.end());

  std::for_each(v.begin(),v.end(),[](int& x) -> void { x = x * 2; });

  // for_each(Iterator begin, Iterator end, UnaryFunction fn)
  std::for_each(v.begin(),v.end(),[](int x) -> void { std::cout << x << ","; });
  std::cout << "\n";

  int factor = 5;
  auto sum = [factor](int x, int y) -> int { return factor * (x + y); };
 
  // accumulate(Iterator begin, Iterator end, T start_value, BinaryFunction fn)
  int total = std::accumulate(v.begin(), v.end(), 0, sum);
  std::cout << "Total: " << total << "\n";

  return 0;
}
