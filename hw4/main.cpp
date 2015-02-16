/* File: main.cpp
   Edited by: Christian DeLozier (delozier@cis)
   Original Author: Richard Eisenberg (eir@cis)
   Desc: testing program for BigInt
*/

#include <iostream>
#include <string>
#include "bigint.hpp"

using namespace std;

void test(const string& label, const BigInt& b, long expected)
{
  if((long)b != expected)
  {
    cout << label << " failed: " << (long)b << " != " << expected << "." << endl;
  }
}

void test(const string& label, bool real, bool expected)
{
  if(real != expected)
  {
    cout << label << " failed: " << real << " != " << expected << "." << endl;
  }
}

int main()
{
  BigInt b = 5;
  test("basic", b, 5);
  b++;
  test("postinc", b, 6);
  b--;
  test("postdec", b, 5);
  --b;
  test("predec", b, 4);
  ++b;
  test("preinc", b, 5);

  BigInt c = 10;
  test("+", b + c, 15);
  test("-", c - b, 5);
  test("-wrongway", b - c, -5);
  test("*", b * c, 50);
  test("neg", -c, -10);
  test("mixed+", b + -c, -5);
  test("mixed-", c - -b, 15);
  
  test("==", b + b == c, true);
  test("==f", b + b + b == c, false);
  test("!=", b != c, true);
  test("<", b < c, true);
  test(">", c > b, true);

  BigInt big = 10000000000L;
  if((long)big != 10000000000L)
  {
    cout << "(long) failed" << endl;
  }

  cout << "Finished running tests!\n";

  return 0;
}
