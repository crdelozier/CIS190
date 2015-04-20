#include <string>
#include <boost/regex.hpp>

int main(){
  std::string str("abc17");
  boost::smatch what;
  boost::regex expression("([a-z]+)(\\d+)");

  std::cout << boost::regex_match(str,what,expression) << "\n";

  std::cout << what.size() << "\n";
  std::cout << what[2] << "\n";

  return 0;
}
