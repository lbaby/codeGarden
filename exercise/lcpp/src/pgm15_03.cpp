//
//   This file contains the C++ code from Program 15.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_03.cpp
//
template <class T>
class InsertionSorter : public Sorter<T> {};

template <class T>
class ExchangeSorter : public Sorter<T> {};

template <class T>
class SelectionSorter : public Sorter<T> {};

template <class T>
class MergeSorter : public Sorter<T> {};

template <class T>
class DistributionSorter : public Sorter<T> {};
