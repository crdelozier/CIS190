/* File: bigint.cpp
   Edited by: Christian DeLozier (delozier@cis)
   Original Author: Richard Eisenberg (eir@cis)
   Desc: implements a decimal-digit-based big integer class
*/

#include "bigint.hpp"

BigInt::BigInt()
{
  for(int i = 0; i < num_digits; i++)
  {
    digits[i] = 0;
  }

  negative = false;
}

BigInt::BigInt(long n)
{
  for(int i = 0; i < num_digits; i++)
  {
    digits[i] = 0;
  }

  negative = (n < 0);

  for(int i = 0; n != 0; i++, n /= 10)
  {
    digits[i] = abs(n % 10);
  }
}

BigInt::BigInt(const BigInt& bi)
{
  for(int i = 0; i < num_digits; i++)
  {
    digits[i] = bi.digits[i];
  }

  negative = bi.negative;
}

BigInt BigInt::operator-() const
{
  BigInt result(*this);
  result.negative = !result.negative;
  return result;
}

BigInt operator+(BigInt lhs, const BigInt& rhs)
{
  lhs += rhs;
  return lhs;
}

BigInt operator-(BigInt lhs, const BigInt& rhs)
{
  lhs -= rhs;
  return lhs;
}

BigInt operator*(BigInt lhs, const BigInt& rhs)
{
  lhs *= rhs;
  return lhs;
}

void BigInt::operator=(const BigInt& bi)
{
  for(int i = 0; i < num_digits; i++)
  {
    digits[i] = bi.digits[i];
  }

  negative = bi.negative;
}

void BigInt::operator+=(const BigInt& bi)
{
  if(negative != bi.negative)
  {
    *this -= -bi;
  }
  else
  {
    int carry = 0;
    for(int i = 0; i < num_digits; i++)
    {
      digits[i] += bi.digits[i] + carry;
      if(digits[i] >= 10)
      {
	    digits[i] -= 10;
	    carry = 1;
      }
      else
      {
	    carry = 0;
      }
    }
  }
}

void BigInt::operator-=(const BigInt& bi)
{
  if(negative != bi.negative)
  {
    *this += -bi;
  }
  else if(*this < bi)
  {
    BigInt result = bi;
    result -= *this;
    *this = result;
    negative = !negative;
  }
  else
  {
    int borrow = 0;
    for(int i = 0; i < num_digits; i++)
    {
      digits[i] -= bi.digits[i] + borrow;
      if(digits[i] < 0)
      {
	    borrow = 1;
	    digits[i] += 10;
      }
      else
      {
        borrow = 0;
      }
    }
  }
}

void BigInt::operator*=(const BigInt& bi)
{
  BigInt intermediates[num_digits];

  for(int lower_digit = 0; lower_digit < num_digits; lower_digit++)
  {
    int carry = 0;
    for(int upper_digit = 0; upper_digit < num_digits; upper_digit++)
    {
      int index = upper_digit + lower_digit;
      if(index < num_digits)
      {
        intermediates[lower_digit].digits[index] =
        digits[upper_digit] * bi.digits[lower_digit] + carry;
	
	    carry = intermediates[lower_digit].digits[index] / 10;
	    intermediates[lower_digit].digits[index] %= 10;
      }
    }
  }

  for(int i = 1; i < num_digits; i++)
  {
    intermediates[0] += intermediates[i];
  }

  *this = intermediates[0];

  negative = negative != bi.negative;
}

bool operator==(const BigInt& lhs, const BigInt& rhs)
{
  bool zero = true;
  for(int i = 0; i < BigInt::num_digits; i++)
  {
    if(lhs.digits[i] != rhs.digits[i])
    {
      return false;
    }
    if(lhs.digits[i] != 0)
    {
      zero = false;
    }
  }

  return lhs.negative == rhs.negative || zero;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
  return !(lhs == rhs);
}

bool operator<(const BigInt& lhs, const BigInt& rhs)
{
  if(lhs.negative && !rhs.negative)
  {
    return true;
  }
  if(!lhs.negative && rhs.negative)
  {
    return false;
  }

  for(int i = BigInt::num_digits - 1; i >= 0; i--)
  {
    if(lhs.digits[i] < rhs.digits[i])
    {
      return !lhs.negative;
    }
    else if(lhs.digits[i] > rhs.digits[i])
    {
      return lhs.negative;
    }
  }

  return false;
}

bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
  return (lhs == rhs) || (lhs < rhs);
}

bool operator>(const BigInt& lhs, const BigInt& rhs)
{
  return !(lhs <= rhs);
}

bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
  return !(lhs < rhs);
}

BigInt& BigInt::operator++()
{
  *this += 1;
  return *this;
}

BigInt& BigInt::operator--()
{
  *this -= 1;
  return *this;
}

BigInt BigInt::operator++(int)
{
  BigInt tmp(*this);
  operator++();
  return tmp;
}

BigInt BigInt::operator--(int)
{
  BigInt tmp(*this);
  operator--();
  return tmp;
}

BigInt::operator long() const
{
  if(negative)
  {
    return -(long)(-*this);
  }
  else
  {
    BigInt max_int = std::numeric_limits<long>::max();
    if(*this <= max_int)
    {
      long result = 0;
      for(int i = num_digits - 1; i >= 0; i--)
      {
	    result *= 10;
	    result += digits[i];
      }
      return result;
    }
    else
    {
      return 0;
    }
  }
}

std::ostream& operator<<(std::ostream& out, const BigInt& bi)
{
  if(bi.negative)
  {
    out << '-';
  }

  bool printing = false;
  for(int i = bi.num_digits - 1; i >= 0; i--)
  {
    if(bi.digits[i] != 0)
    {
      printing = true;
    }

    if(printing)
    {
      out << bi.digits[i];
    }
  }
      
  return out;
}
