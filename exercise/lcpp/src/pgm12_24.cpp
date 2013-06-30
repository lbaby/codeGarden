//
//   This file contains the C++ code from Program 12.24 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_24.cpp
//
void EquivalenceClasses ()
{
    unsigned int n;
    cin >> n;
    Partition& p = *new PartitionAsForest (n);

    unsigned int i;
    unsigned int j;
    while (cin >> i >> j, !cin.eof ())
    {
	Set& s = p.Find (Set::Element (i)));
	Set& t = p.Find (Set::Element (j)));
	if (s != t)
	    p.Join (s, t);
	else
	    cout << "redundant pair: "
		<< i << ", " << j << endl;
    }
    cout << p << endl;
    delete &p;
}
