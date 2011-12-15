//
//   This file contains the C++ code from Program 8.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_01.cpp
//

#include <Hash.h>
#include <cmath>
#include <string>


HashValue Hash (char c)
    { return abs (c); }

HashValue Hash (int i)
    { return abs (i); }

    HashValue Hash (double d)
{
    if (d == 0)
	return 0;
    else
    {
	int exponent;
	double mantissa = std::frexp (d, &exponent);
	return (2 *static_cast<unsigned int >(  fabs (mantissa))  - 1) * ~0U;
    }
}
    



HashValue Hash (std::string const& s)
{
    HashValue result = 0;
    for (unsigned int i = 0; s [i] != 0; ++i)
	result = (result & mask) ^ (result << shift) ^ s [i];
    return result;
}


enum { __num_primes = 28 };

static const unsigned int  __prime_list[__num_primes] =
{
  53U,         97U,         193U,       389U,       769U,
  1543U,       3079U,       6151U,      12289U,     24593U,
  49157U,      98317U,      196613U,    393241U,    786433U,
  1572869U,    3145739U,    6291469U,   12582917U,  25165843U,
  50331653U,   100663319U,  201326611U, 402653189U, 805306457U, 
  1610612741U, 3221225473U, 4294967291U
};

unsigned  int SuitablePrime(unsigned int len)
{
	unsigned int i = 0;
	for(; i < __num_primes; ++i){
		if (__prime_list[i] >= len){
			break;
		}
	}
	
	return __prime_list[i];
}

	
