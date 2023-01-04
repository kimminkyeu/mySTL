/* Compute complex natural logarithm. */

/* Copyright (C) 1997-1999 Free Software Foundation, Inc.

   This file is part of the GNU ISO C++ Library.  This library is free
   software; you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option)
   any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this library; see the file COPYING.  If not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.

   As a special exception, you may use this file as part of a free software
   library without restriction.  Specifically, if other files instantiate
   templates or use macros or inline functions from this file, or you compile
   this file and link it with other files to produce an executable, this
   file does not by itself cause the resulting executable to be covered by
   the GNU General Public License.  This exception does not however
   invalidate any other reasons why the executable file might be covered by
   the GNU General Public License.  */


#include <math.h>
#include "mathconf.h"

/* Thanks to SGI we have to trick here.  At least Irix 6.2 provides hypotl,
   but it has a wrong prototype.  Grrr.  */
extern long double local_hypotl (long double, long double) asm ("hypotl");


__complex__ long double
c_logl (__complex__ long double x)
{
  __complex__ long double result;

  if (x == 0.0)
    {
      /* Real and imaginary part are 0.0.  */
      __imag__ result = signbit (__real__ x) ? M_PI : 0.0;
      __imag__ result = copysignl (__imag__ result, __imag__ x);
      /* Yes, the following line raises an exception.  */
      __real__ result = -1.0 / fabsl (__real__ x);
    }
  else if (__real__ x == __real__ x && __imag__ x == __imag__ x)
    {
      /* Neither real nor imaginary part is NaN.  */
      __real__ result = logl (local_hypotl (__real__ x, __imag__ x));
      __imag__ result = atan2l (__imag__ x, __real__ x);
    }
  else
    {
      __imag__ result = NAN;
      if (INFINITEL_P (__real__ x) || INFINITEL_P (__imag__ x))
	/* Real or imaginary part is infinite.  */
	__real__ result = HUGE_VALL;
      else
	__real__ result = NAN;
    }

  return result;
}
