//
//   This file contains the C++ code from Program 8.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_23.cpp
//
class Counter : public Int
{
public:
    Counter (int i) : Int (i)
	{}
    void operator ++ ()
	{ ++datum; }
};

void CountWords (HashTable& table)
{
    std::string word; 
    while (cin >> word, !cin.eof ())
    {
	Object& obj =
	    table.Find (Association (*new String (word)));
	if (obj.IsNull ())
	    table.Insert (*new Association (
		*new String (word), *new Counter (1)));
	else
	{
	    Association& assoc =
		dynamic_cast<Association&> (obj);
	    Counter& i =
		dynamic_cast<Counter&> (assoc.Value ());
	    ++i;
	}
    }
    cout << table << endl;
}
