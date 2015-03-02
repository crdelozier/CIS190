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
  BigInt a(0);
  test("constructor-zero", a, 0);

  BigInt a2(255);
  test("constructor-non-zero", a2, 255);

  BigInt a3(-2012);
  test("constructor-negative", a3, -2012);
  
  BigInt a4(a2);
  test("copy-constructor-positive", a4, 255);

  BigInt a5(a3);
  test("copy-constructor-negative", a5, -2012);

  BigInt b = 5;
  test("basic", b, 5);
  a = b++;
  test("postinc-result", a, 5);
  test("postinc", b, 6);
  a = b--;
  test("postdec-result", a, 6);
  test("postdec", b, 5);
  a = --b;
  test("predec-result", a, 4);
  test("predec", b, 4);
  a = ++b;
  test("preinc-result", a, 5);
  test("preinc", b, 5);

  BigInt c = 10;
  test("+", b + c, 15);
  test("-", c - b, 5);
  test("*", b * c, 50);
  test("neg", -c, -10);

  test("non-mutable", b, 5); // ***
  test("non-mutable-2", c, 10); // ***

  c += 12;
  test("+=", c, 22);
  c -= 10;
  test("-=", c, 12);
  c *= 2;
  test("*=", c, 24);

  BigInt d = c;
  test("operator=(different)",d,24);

  d = d;
  test("operator=(same)",d,24);
  
  c = 10;

  test("==", b + b == c, true);
  test("!=", b != c, true);
  test("<", b < c, true);

  BigInt big = 5000000000000L;
  if((long)big != 5000000000000L)
  {
    cout << "(long) failed" << endl;
  }

  cout << "Finished running tests!\n";

  return 0;
}
