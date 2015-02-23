#include <iostream>
#include <fstream>
#include <ostream>

void print(std::ostream &out){
  out << "Hello World!\n";
}

int main(){
  std::fstream file("output.txt", std::ios_base::out);

  print(file);
  print(std::cout);

  file.close();

  return 0;
}
