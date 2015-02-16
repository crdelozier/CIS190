/* File: bigint.cpp
   Edited by: Christian DeLozier (delozier@cis)
   Original Author: Richard Eisenberg (eir@cis)
   Desc: implements a decimal-digit-based big integer class
*/

#include "bigint.hpp"

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
