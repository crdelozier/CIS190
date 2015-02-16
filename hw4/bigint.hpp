/* File: bigint.hpp
   Edited by: Christian DeLozier (delozier@cis)
   Original Author: Richard Eisenberg (eir@cis)
   Desc: Header for the BigInt class
*/

#pragma once

#include <cstdlib>
#include <limits>
#include <iostream>

class BigInt
{
 private:
  static const int num_digits = 100;
  int digits[num_digits];
  bool negative;

 public:
  BigInt(); // initializes to 0
  BigInt(long l);

  BigInt(const BigInt& bi); // copy constructor

  BigInt operator-() const; // negation

  // basic arithmetic
  friend BigInt operator+(BigInt lhs, const BigInt& rhs);
  friend BigInt operator-(BigInt lhs, const BigInt& rhs);
  friend BigInt operator*(BigInt lhs, const BigInt& rhs);

  // assignment
  void operator=(const BigInt& bi);

  // compound assignment (recall: a += b is equivalent to a = a + b)
  void operator+=(const BigInt& bi);
  void operator-=(const BigInt& bi);
  void operator*=(const BigInt& bi);

  // comparisons
  friend bool operator==(const BigInt& lhs, const BigInt& rhs);
  friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
  friend bool operator<(const BigInt& lhs, const BigInt& rhs);
  friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
  friend bool operator>(const BigInt& lhs, const BigInt& rhs);
  friend bool operator>=(const BigInt& lhs, const BigInt& rhs);

  // increment/decrement
  BigInt& operator++(); // prefix, return new value
  BigInt& operator--(); // prefix, return new value
  BigInt operator++(int); // postfix, must return original value
  BigInt operator--(int); // postfix, must return original value

  // conversions -- they return 0 when invalid (out of range)
  explicit operator long() const;

  // print a BigInt:
  friend std::ostream& operator<<(std::ostream& out, const BigInt& bi);
};
