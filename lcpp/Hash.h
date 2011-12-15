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

#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <stdlib.h>

#ifdef C99
	#include <stdint.h>
	typedef uint32_t  HashValue;
#else
 	typedef unsigned int HashValue;
 #endif

#define    bitsizeof(T)\
	  (sizeof(T)* 8)

HashValue Hash (char c);
HashValue Hash (int i);

HashValue Hash (std::string const& s);
    HashValue Hash (double d);
    
unsigned  int SuitablePrime(unsigned int len);

unsigned int const shift = 6;
HashValue const mask = ~0U << (bitsizeof (HashValue) - shift);

#endif /*HASH_H_*/
