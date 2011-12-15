//
//   This file contains the C++ code from Program 6.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_12.cpp
//
void RPNCalculator (Stack& stack)
{
    char c;
    while (cin >> c, !cin.eof ())
    {
	if (std::isdigit (c))
	    stack.Push (*new Int (c - '0'));
	else if (c == '+')
	{
	    Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
	    Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
	    stack.Push (*new Int (arg1 + arg2));
	    delete &arg1;
	    delete &arg2;
	}
	else if (c == '*')
	{
	    Int& arg2 = dynamic_cast<Int&> (stack.Pop ());
	    Int& arg1 = dynamic_cast<Int&> (stack.Pop ());
	    stack.Push (*new Int (arg1 * arg2));
	    delete &arg1;
	    delete &arg2;
	}
	else if (c == '=')
	{
	    Int& arg = dynamic_cast<Int&> (stack.Pop ());
	    cout << arg << endl;
	    delete &arg;
	}
    }
}
