#include <string>
#include <boost/regex.hpp>

int main(){
  std::string str("abc17");
  boost::regex expression("(\\w+)(\\d+)");
  
  std::cout << boost::regex_match(str,expression) << "\n";
  
  return 0;
}
