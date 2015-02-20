#include <iostream>

class Foo{
public:
  static int x;

  static void setX();
};

int Foo::x = 0;

void Foo::setX(){
  x = 1;
}

// char* str_tok(char *str, char *token){
//   static char *old_str = NULL;

//   if(str == NULL){
//     str = old_str;
//   }else{
//     old_str = str;
//   }

//   ...
// }

void print_int(int x){
  static int value = 0;
  int value2 = 0;
  std::cout << "Value: " << value << "\n";
  value = x;
}

int main(){
  print_int(5);
  print_int(10);
  print_int(15);

  return 0;
}
